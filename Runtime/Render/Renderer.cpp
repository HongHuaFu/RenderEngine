#include "Renderer.hpp"
#include "CommandBuffer.hpp"
#include "GraphicsCache.hpp"

#include "../Geometry/Quad.hpp"
#include "../Render/Mesh.hpp"
#include "../Render/Shader.hpp"
#include "../Render/Material.hpp"

#include "../Scene/FlyCamera.hpp"

namespace RE
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
		delete m_GraphicCache;
		delete m_CommandBuffer;
		delete m_NDCQuad;
	}

	void Renderer::Init()
	{
		m_CommandBuffer = new CommandBuffer(this);
		m_GraphicCache = new GraphicCache();
		m_NDCQuad = new Quad();

		m_GraphicCache->SetDepthTest(true);
		m_GraphicCache->SetCull(true);

		// 开启CubeMap边缘采样混合
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0f);


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

	void Renderer::RenderCustomCommand(RenderCommand* command,FlyCamera* customCamera,bool updateGLSettings)
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
			material->GetShader()->SetMatrix("projection", customCamera->GetProjectMatrix());
			material->GetShader()->SetMatrix("view",customCamera->GetViewMatrix());
			material->GetShader()->SetVector("camPos",customCamera->Position);
		}

		material->GetShader()->SetMatrix("model", command->Transform);
		material->GetShader()->SetMatrix("prevModel", command->PrevTransform);

		// TODO: 需要完善
	}



}
