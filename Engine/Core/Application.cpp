#include "Application.hpp"
#include "Macro.hpp"

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
		
		m_Window = std::make_unique<Window>(props);
		m_Window->SetEventCallback(BIND_FN(Application::OnEvent));
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
		while(m_Running)
		{
			
			m_Window->OnUpdate();
		}
	}
}