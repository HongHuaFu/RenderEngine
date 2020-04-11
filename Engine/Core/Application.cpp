#include "Application.hpp"
#include "Macro.hpp"
#include "Window.hpp"
#include "../Event/WindowEvent.hpp"

#include "../IO/Loader.hpp"
#include "../Renderer/Renderer.hpp"
#include "../UI/UI.hpp"

#include "../Vendor/imgui.h"
#include "../Vendor/imgui_impl_glfw.h"
#include "../Vendor/imgui_impl_opengl3.h"
#include "../Renderer/RenderTarget.hpp"


namespace Engine
{
	Application* Application::s_Instance = nullptr;

	Application::Application(unsigned int window_width,
							 unsigned int window_height,
							 const char * title)
	{
		s_Instance = this;

		WindowProps props;
		if(window_width != 0 && window_height != 0)
		{
			props.Height = window_height;
			props.Width = window_width;
			props.Title = title;
		}
		
		m_Window = new Window(props);
		m_Window->SetEventCallback(BIND_FN(Application::OnEvent));

		// 初始化资源加载器
		Loader::Init();

		m_Renderer = new Renderer();
		m_Renderer->Init();
		m_Renderer->SetRenderSize(m_Window->GetWidth(),m_Window->GetHeight());

		m_SceneRT = new RenderTarget(1,1,GL_UNSIGNED_BYTE,1,false);
		m_UI = new UI(m_Window);

	}


	Application::~Application()
	{
		
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(Application::OnWindowResize));
	}

	void Application::DrawScene(RenderTarget* rt)
	{
		ImGui::Begin("Scene");

		ImVec2 canvas_pos = ImGui::GetCursorScreenPos();            
		ImVec2 canvas_size = ImGui::GetWindowSize();
		
		EventDrawScene(canvas_size.x,canvas_size.y,rt);

		ImGui::GetWindowDrawList()->AddImage(
			(void*)(intptr_t)rt->GetColorTexture(0)->GetID(), 
			ImVec2(ImGui::GetCursorScreenPos()),
			ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), 
			ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
	}



	bool Application::OnWindowClose(WindowCloseEvent&)
	{
		m_Running = false;
		return true;
	}


	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		EventWindowResize(e);
		return false;
	}


	void Application::Run()
	{


		EventStart();

		while(m_Running)
		{
			

			EventUpdate();
			m_Window->OnUpdate();

		
			m_UI->UIStart();
			EventDrawUI();
			DrawScene(m_SceneRT);
			m_UI->UIEnd();


			m_Window->SwapBuffer();
		}
	}
}