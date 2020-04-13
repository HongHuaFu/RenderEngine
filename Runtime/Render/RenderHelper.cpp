#include "RenderHelper.hpp"
#include "../Render/CommandBuffer.hpp"
#include "../Scene/SceneNode.hpp"
#include "../Scene/Camera.hpp"
#include "../Render/TextureCube.hpp"
#include "../Render/Material.hpp"
#include "../Core/Macro.hpp"
#include "../Render/Renderer.hpp"
#include "../Render/RenderTarget.hpp"
#include "../Geometry/Quad.hpp"

#include <stack>
#include <vector>

namespace RE
{
	RenderHelper::RenderHelper(Renderer* r)
	{
		m_Renderer = r; 
		m_Quad = new Quad();
		glGenFramebuffers(1, &m_FramebufferCubemap);
		glGenRenderbuffers(1, &m_CubemapDepthRBO);
	}

	RenderHelper::~RenderHelper()
	{
		delete m_Quad;
		glDeleteFramebuffers(1,&m_FramebufferCubemap);
		glDeleteRenderbuffers(1,&m_CubemapDepthRBO);
	}

	// 将当前场景节点渲染到一个CubeMap中
	void RenderHelper::RenderToCubeMap(SceneNode* scene,TextureCube* target,glm::vec3 position,unsigned int mipLevel)
	{
		// 构建一个CommandBuffer
		CommandBuffer commandBuffer(m_Renderer);

		// 先压入父节点的渲染命令,分组的fbo设置为默认/但是并不提交到最终的渲染buffer，仅作为临时buffer
		commandBuffer.Push(scene->Mesh, scene->Material, scene->GetTransform());
		
		// 先序遍历子节点 使用辅助栈压入
		std::stack<SceneNode*> childStack;
		for (unsigned int i = 0; i < scene->GetChildCount(); ++i)
			childStack.push(scene->GetChildByIndex(i));

		while (!childStack.empty())
		{
			SceneNode *child = childStack.top();
			childStack.pop();

			// 子节点网格压入渲染队列
			commandBuffer.Push(child->Mesh, child->Material, child->GetTransform());

			// 一次先序遍历
			for (unsigned int i = 0; i < child->GetChildCount(); ++i)
				childStack.push(child->GetChildByIndex(i));
		}

		// 排序
		commandBuffer.Sort();

		// 关闭视锥体剔除
		std::vector<RenderCommand> renderCommands = commandBuffer.GetCustomRenderCommands(nullptr);

		RenderToCubemap(renderCommands, target, position, mipLevel);
	}

	void RenderHelper::RenderToCubemap(std::vector<RenderCommand>& renderCommands,TextureCube* target,glm::vec3 position,unsigned int mipLevel)
	{
		Camera faceCameras[6] = {
			//相机放在中央 向NDC立方体的六个方向看去，fov设为90度，这时正好是1/6个立方体（一个等四棱锥）
			Camera(position, glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			Camera(position, glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			Camera(position, glm::vec3(0.0f,1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
			Camera(position, glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f,-1.0f)),
			Camera(position, glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			Camera(position, glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
		};

		// 根据mip等级调整最终渲染的宽高
		float width = (float)target->m_FaceWidth * pow(0.5, mipLevel);
		float height = (float)target->m_FaceHeight * pow(0.5, mipLevel);

		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferCubemap);
		glBindRenderbuffer(GL_RENDERBUFFER, m_CubemapDepthRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
			m_CubemapDepthRBO);

		// 视口大小调整
		glViewport(0, 0, width, height);

		// 绑定到对应的FBO
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferCubemap);

		for (unsigned int i = 0; i < 6; ++i)
		{
			Camera *camera = &faceCameras[i];

			// 相机矩阵调整
			// 角度设为90度，这时正好为1/6立方体，其中中心为相机
			camera->SetPerspective(glm::radians(90.0f), width / height, 0.1f, 100.0f);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, target->m_ID, mipLevel);

			// 渲染前清除
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (unsigned int i = 0; i < renderCommands.size(); ++i)
			{
				// 生成立方体贴图的材质类型应该为custom
				LOG_ASSERT(renderCommands[i].Material->Type == MaterialType::CUSTOM);
				m_Renderer->RenderCustomCommand(&renderCommands[i], camera);
			}
		}
	}

	void RenderHelper::Blit(Texture* src,Material* material,RenderTarget* dst,std::string textureUniformName)
	{
		// 若设置了目标fbo则绑定目标fbo
		if (dst)
		{
			glViewport(0, 0, dst->m_Width, dst->m_Height);
			glBindFramebuffer(GL_FRAMEBUFFER, dst->m_ID);
			if (dst->m_HasDepthAndStencil)
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			else
				glClear(GL_COLOR_BUFFER_BIT);
		}
		else
		{
			// 使用默认的fbo
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, m_Renderer->m_RenderSize.x, m_Renderer->m_RenderSize.y);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		// 没有赋予后处理材质则直接返回
		if (!material)
		{
			// TODO: 修改为默认材质
			return;
		}
		
		// 设置原贴图
		if (src)
		{
			material->SetTexture(textureUniformName, src, 0);
		}
		
		// 构造一次全屏的后处理
		RenderCommand command;
		command.Material = material;
		command.Mesh = m_Quad;
		m_Renderer->RenderCustomCommand(&command, nullptr);
	}
}
