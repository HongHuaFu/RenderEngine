#include "Application.hpp"
#include "Macro.hpp"
#include "Window.hpp"

#include "../Event/Event_Window.hpp"
#include "../Event/Event.hpp"


namespace RE
{
	Application::Application(unsigned int window_width,unsigned int window_height,const char * title)
	{
		WindowProps props;
		if(window_width != 0 && window_height != 0)
		{
			props.Height = window_height;
			props.Width = window_width;
			props.Title = title;
		}

		m_Window = new Window(props);
		m_Window->SetEventCallback(BIND_FN(Application::OnEvent));
	}


	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<EventWindowClose>(BIND_FN(Application::OnWindowClose));
		dispatcher.Dispatch<EventWindowResize>(BIND_FN(Application::OnWindowResize));

		// TODO: 处理其它类型事件

	}


	bool Application::OnWindowClose(EventWindowClose&)
	{
		m_Running = false;
		return true;
	}


	bool Application::OnWindowResize(EventWindowResize& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		return false;
	}


	void Application::Run()
	{
		OnStart();
		while(m_Running)
		{
			OnUpdate();
			m_Window->OnUpdate();
		}
	}
}