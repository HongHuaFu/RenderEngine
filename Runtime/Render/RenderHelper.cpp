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

	// ����ǰ�����ڵ���Ⱦ��һ��CubeMap��
	void RenderHelper::RenderToCubeMap(SceneNode* scene,TextureCube* target,glm::vec3 position,unsigned int mipLevel)
	{
		// ����һ��CommandBuffer
		CommandBuffer commandBuffer(m_Renderer);

		// ��ѹ�븸�ڵ����Ⱦ����,�����fbo����ΪĬ��/���ǲ����ύ�����յ���Ⱦbuffer������Ϊ��ʱbuffer
		commandBuffer.Push(scene->Mesh, scene->Material, scene->GetTransform());
		
		// ��������ӽڵ� ʹ�ø���ջѹ��
		std::stack<SceneNode*> childStack;
		for (unsigned int i = 0; i < scene->GetChildCount(); ++i)
			childStack.push(scene->GetChildByIndex(i));

		while (!childStack.empty())
		{
			SceneNode *child = childStack.top();
			childStack.pop();

			// �ӽڵ�����ѹ����Ⱦ����
			commandBuffer.Push(child->Mesh, child->Material, child->GetTransform());

			// һ���������
			for (unsigned int i = 0; i < child->GetChildCount(); ++i)
				childStack.push(child->GetChildByIndex(i));
		}

		// ����
		commandBuffer.Sort();

		// �ر���׶���޳�
		std::vector<RenderCommand> renderCommands = commandBuffer.GetCustomRenderCommands(nullptr);

		RenderToCubemap(renderCommands, target, position, mipLevel);
	}

	void RenderHelper::RenderToCubemap(std::vector<RenderCommand>& renderCommands,TextureCube* target,glm::vec3 position,unsigned int mipLevel)
	{
		Camera faceCameras[6] = {
			//����������� ��NDC���������������ȥ��fov��Ϊ90�ȣ���ʱ������1/6�������壨һ��������׶��
			Camera(position, glm::vec3(1.0f, 0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			Camera(position, glm::vec3(-1.0f, 0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			Camera(position, glm::vec3(0.0f,1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
			Camera(position, glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f,-1.0f)),
			Camera(position, glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			Camera(position, glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
		};

		// ����mip�ȼ�����������Ⱦ�Ŀ��
		float width = (float)target->m_FaceWidth * pow(0.5, mipLevel);
		float height = (float)target->m_FaceHeight * pow(0.5, mipLevel);

		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferCubemap);
		glBindRenderbuffer(GL_RENDERBUFFER, m_CubemapDepthRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
			m_CubemapDepthRBO);

		// �ӿڴ�С����
		glViewport(0, 0, width, height);

		// �󶨵���Ӧ��FBO
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferCubemap);

		for (unsigned int i = 0; i < 6; ++i)
		{
			Camera *camera = &faceCameras[i];

			// ����������
			// �Ƕ���Ϊ90�ȣ���ʱ����Ϊ1/6�����壬��������Ϊ���
			camera->SetPerspective(glm::radians(90.0f), width / height, 0.1f, 100.0f);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, target->m_ID, mipLevel);

			// ��Ⱦǰ���
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (unsigned int i = 0; i < renderCommands.size(); ++i)
			{
				// ������������ͼ�Ĳ�������Ӧ��Ϊcustom
				LOG_ASSERT(renderCommands[i].Material->Type == MaterialType::CUSTOM);
				m_Renderer->RenderCustomCommand(&renderCommands[i], camera);
			}
		}
	}

	void RenderHelper::Blit(Texture* src,Material* material,RenderTarget* dst,std::string textureUniformName)
	{
		// ��������Ŀ��fbo���Ŀ��fbo
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
			// ʹ��Ĭ�ϵ�fbo
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, m_Renderer->m_RenderSize.x, m_Renderer->m_RenderSize.y);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		// û�и�����������ֱ�ӷ���
		if (!material)
		{
			// TODO: �޸�ΪĬ�ϲ���
			return;
		}
		
		// ����ԭ��ͼ
		if (src)
		{
			material->SetTexture(textureUniformName, src, 0);
		}
		
		// ����һ��ȫ���ĺ���
		RenderCommand command;
		command.Material = material;
		command.Mesh = m_Quad;
		m_Renderer->RenderCustomCommand(&command, nullptr);
	}
}
