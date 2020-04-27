#include <Api.hpp>
#include <Core/EntryPoint.hpp>

#include "Editor.hpp"



namespace RE
{
	class Sandbox : public Application
	{
	public:
		virtual void OnStart() override
		{
			m_Renderer = new Renderer();
			m_Renderer->Init();
			m_Renderer->SetRenderSize(m_Window->GetWidth(), m_Window->GetHeight());

			m_SkyBox = new SkyBox();
			m_SkyBox->SetCubemap(m_Renderer->m_PP_PBRIBLForward->GetSkyBoxCubemap());

			RE::Scene::Root->AddChild(m_SkyBox);

			m_Editor = new Editor();
			m_Editor->OnStart((GLFWwindow*)(m_Window->GetNativeWindow()),m_Renderer);
		}


		virtual void OnUpdate() override
		{
			float currentFrameTime = glfwGetTime();

			if(lastFrameTime < 0.001f)
			{
				lastFrameTime = currentFrameTime;
			}

			deltaTime = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;

			

			if(EventKey::keysPressed[GLFW_KEY_W]||EventKey::keysPressed[GLFW_KEY_UP])
			{
				m_Renderer->m_Camera->InputKey(deltaTime, CAMERA_MOVEMENT::FORWARD);
				LOG_TRACE("Press W/Up key.");
			}
			if (EventKey::keysPressed[GLFW_KEY_S] || EventKey::keysPressed[GLFW_KEY_DOWN])
				m_Renderer->m_Camera->InputKey(deltaTime, CAMERA_MOVEMENT::BACK);
			if (EventKey::keysPressed[GLFW_KEY_A] || EventKey::keysPressed[GLFW_KEY_LEFT])
				m_Renderer->m_Camera->InputKey(deltaTime, CAMERA_MOVEMENT::LEFT);
			if (EventKey::keysPressed[GLFW_KEY_D] || EventKey::keysPressed[GLFW_KEY_RIGHT])
				m_Renderer->m_Camera->InputKey(deltaTime, CAMERA_MOVEMENT::RIGHT);
			if (EventKey::keysPressed[GLFW_KEY_E])
				m_Renderer->m_Camera->InputKey(deltaTime, CAMERA_MOVEMENT::UP);
			if (EventKey::keysPressed[GLFW_KEY_Q])
				m_Renderer->m_Camera->InputKey(deltaTime, CAMERA_MOVEMENT::DOWN);
			
			m_Editor->OnTick();

			m_Renderer->m_Camera->Update(deltaTime);


			m_Renderer->PushRender(RE::Scene::Root);
			m_Renderer->RenderPushedCommands(m_Renderer->m_PP_PBRIBLForward);


			
			m_Editor->PushRender();
		}

	private:
		SkyBox* m_SkyBox;
		float deltaTime  = 0.0f;
		float lastFrameTime = 0.0f;
		Editor* m_Editor;
	public:
		~Sandbox(){ delete m_SkyBox; }
	};

	Application* CreateApplication()
	{
		return new Sandbox();
	}
}

