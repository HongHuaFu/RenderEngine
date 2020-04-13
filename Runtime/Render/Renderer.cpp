#include "Renderer.hpp"
#include "CommandBuffer.hpp"
#include "GraphicsCache.hpp"

#include "../Geometry/Quad.hpp"
#include "../Render/Mesh.hpp"
#include "../Render/Shader.hpp"
#include "../Render/Material.hpp"
#include "../Render/TextureCube.hpp"
#include "../Render//Texture.hpp"
#include "../Scene/Camera.hpp"
#include "../Scene/SceneNode.hpp"
#include "../Core/Macro.hpp"
#include "../Render/Pipeline.hpp"
#include "../Render/PBRPipeline.hpp"
#include <vector>
#include <stack>

namespace RE
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
		delete m_GraphicCache;
		delete m_CommandBuffer;
		delete m_PBRPipeline;
	}

	void Renderer::Init()
	{
		m_CommandBuffer = new CommandBuffer(this);
		m_GraphicCache = new GraphicCache();
		m_PBRPipeline = new PBRPipeline();

		m_GraphicCache->SetDepthTest(true);
		m_GraphicCache->SetCull(true);

		// 开启CubeMap边缘采样混合
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0f);

		m_PBRPipeline->Start();
	}

	void Renderer::PushRender(Mesh* mesh,Material* material,glm::mat4 transform,glm::mat4 prevFrameTransform)
	{
		RenderTarget* target = GetCurrentRenderTarget();
		m_CommandBuffer->Push(mesh, material, transform, prevFrameTransform, glm::vec3(-99999.0f), glm::vec3(99999.0f), target);
	}

	void Renderer::PushRender(SceneNode* node)
	{
		// 更新节点的Transform矩阵信息
		node->UpdateTransform(true);

		RenderTarget* target = GetCurrentRenderTarget();

		// 先序遍历该节点树 所有的子节点都压入渲染队列中
		std::stack<SceneNode*> nodeStack;
		nodeStack.push(node);
		for (unsigned int i = 0; i < node->GetChildCount(); ++i)
			nodeStack.push(node->GetChildByIndex(i));

		while (!nodeStack.empty())
		{
			SceneNode* node = nodeStack.top();
			nodeStack.pop();

			// 只有带Mesh的节点才会压入渲染缓冲中
			if (node->Mesh)
			{
				glm::vec3 boxMinWorld = node->GetWorldPosition() + (node->GetWorldScale() * node->BoxMin);
				glm::vec3 boxMaxWorld = node->GetWorldPosition() + (node->GetWorldScale() * node->BoxMax);


				m_CommandBuffer->Push(node->Mesh, node->Material, node->GetTransform(), node->GetPrevTransform(), boxMinWorld, boxMaxWorld, target);
			}

			for(unsigned int i = 0; i < node->GetChildCount(); ++i)
				nodeStack.push(node->GetChildByIndex(i));
		}
	}

	void Renderer::RenderMesh(Mesh* mesh,Shader* shader)
	{
		shader->Use();
		glBindVertexArray(mesh->m_VAO);
		if (mesh->Indices.size() > 0)
		{
			glDrawElements(mesh->Topology == TOPOLOGY::TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, mesh->Indices.size(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(mesh->Topology == TOPOLOGY::TRIANGLE_STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES, 0, mesh->Positions.size());
		}
	}

	void Renderer::RenderPushedCommands(Pipeline* pipeline)
	{
		pipeline->RenderPushCommand(this);
	}

	void Renderer::RenderCustomCommand(RenderCommand* command,Camera* customCamera,bool updateGLSettings)
	{
		Material* material = command->Material;
		Mesh* mesh = command->Mesh;

		// 更新GL状态
		if (updateGLSettings)
		{
			m_GraphicCache->SetBlend(material->Blend);
			if(material->Blend)
			{
				m_GraphicCache->SetBlendFunc(material->BlendSrc, material->BlendDst);
			}
			m_GraphicCache->SetDepthFunc(material->DepthCompare);
			m_GraphicCache->SetDepthTest(material->DepthTest);
			m_GraphicCache->SetCull(material->Cull);
			m_GraphicCache->SetCullFace(material->CullFace);
		}

		material->GetShader()->Use();
		// 如果使用的自定义相机。则需要修改全局的UBO
		if (customCamera)
		{
			material->GetShader()->SetMatrix("projection", customCamera->Projection);
			material->GetShader()->SetMatrix("view",customCamera->View);
			material->GetShader()->SetVector("camPos",customCamera->Position);
		}

		material->GetShader()->SetMatrix("model", command->Transform);
		material->GetShader()->SetMatrix("prevModel", command->PrevTransform);

		// TODO: 加入阴影

		// 绑定材质对应Shader的贴图插槽
		auto* samplers = material->GetSamplerUniforms();
		for (auto it = samplers->begin(); it != samplers->end(); ++it)
		{
			if (it->second.Type == Shader_Type::SAMPLERCUBE)
				it->second.TextureCube->Bind(it->second.Unit);
			else
				it->second.Texture->Bind(it->second.Unit);
		}

		// 绑定材质对应Shader的常量值
		auto* uniforms = material->GetUniforms();
		for (auto it = uniforms->begin(); it != uniforms->end(); ++it)
		{
			switch (it->second.Type)
			{
			case Shader_Type::BOOL:
				material->GetShader()->SetBool(it->first, it->second.Bool);
				break;
			case Shader_Type::INT:
				material->GetShader()->SetInt(it->first, it->second.Int);
				break;
			case Shader_Type::FLOAT:
				material->GetShader()->SetFloat(it->first, it->second.Float);
				break;
			case Shader_Type::VEC2:
				material->GetShader()->SetVector(it->first, it->second.Vec2);
				break;
			case Shader_Type::VEC3:
				material->GetShader()->SetVector(it->first, it->second.Vec3);
				break;
			case Shader_Type::VEC4:
				material->GetShader()->SetVector(it->first, it->second.Vec4);
				break;
			case Shader_Type::MAT2:
				material->GetShader()->SetMatrix(it->first, it->second.Mat2);
				break;
			case Shader_Type::MAT3:
				material->GetShader()->SetMatrix(it->first, it->second.Mat3);
				break;
			case Shader_Type::MAT4:
				material->GetShader()->SetMatrix(it->first, it->second.Mat4);
				break;
			default:
				LOG_ERROR("Unrecognized Uniform type set.");
				break;
			}
		}

		RenderMesh(mesh, material->GetShader());
	}



}
