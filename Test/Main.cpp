#include <Engine.hpp>
#include <Core/EntryPoint.hpp>


namespace Engine
{
	class Sandbox : public Application
	{
	public:
		virtual void EventWindowResize(WindowResizeEvent& e) override
		{
			LOG_INFO("Window resize ({0},{1})",e.GetWidth(),e.GetHeight());
		}

		virtual void EventStart() override
		{
			m_Quad = Quad();
			m_Shader = Loader::LoadShader("MikuTex","E:\\RenderEngine\\Resource\\Shader\\Quad.vs",
											    "E:\\RenderEngine\\Resource\\Shader\\Quad.fs");
			Loader::LoadTexture("miku","E:\\RenderEngine\\Resource\\Textures\\Miku.jpg");
			m_Material = new Material(m_Shader);
			
			m_Material->SetTexture("texture_diffuse1",Loader::GetTexture("miku"),0);
		

			m_SkyBox = new SkyBox();
			m_PBREnv = m_Renderer->m_PBR->GetSkyCapture();
			m_SkyBox->SetCubemap(m_PBREnv->Prefiltered);
			float lodLevel = 1.5f; 
			m_SkyBox->Material->SetFloat("lodLevel", lodLevel);

			m_Camera = new FlyCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
			m_Renderer->SetCamera(m_Camera);
			glEnable(GL_DEPTH_TEST);

		}

		virtual void EventUpdate() override
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
		}

		virtual void EventDrawUI() override
		{
			ImGui::ShowDemoWindow();
		}

		virtual void EventDrawScene(unsigned int width,unsigned int height,RenderTarget* rt) override
		{
			rt->ReSize(width,height);
			rt->Bind();
			m_Camera->Update(1.0f);
			m_Renderer->PushRender(m_SkyBox);
			m_Renderer->RenderPushedCommands();
			rt->UnBind();
		}

	private:
		Quad m_Quad;
		Shader* m_Shader;
		Material* m_Material;
		SkyBox* m_SkyBox;
		PBRCapture* m_PBREnv;
		FlyCamera* m_Camera;
	};
	
	Application* CreateApplication()
	{
		return new Sandbox();
	}
}

