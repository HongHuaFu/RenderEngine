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
			m_Shader = Loader::LoadShader("Tex","E:\\RenderEngine\\Resource\\Shader\\Quad.vs",
											    "E:\\RenderEngine\\Resource\\Shader\\Quad.fs");
			Loader::LoadTexture("miku","E:\\RenderEngine\\Resource\\Textures\\Miku.jpg");

			m_Shader->SetInt("texture_diffuse1",0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Loader::GetTexture("miku")->GetID());

			glEnable(GL_DEPTH_TEST);

		}

		virtual void EventUpdate()
		{
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_Shader->Use();
			glBindVertexArray(m_Quad.m_VAO);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Quad.Positions.size());
			glBindVertexArray(0);
		}

	private:
		Quad m_Quad;
		Shader* m_Shader;
	};
	
	Application* CreateApplication()
	{
		return new Sandbox();
	}
}

