#include "Application.hpp"
#include "Macro.hpp"
#include "Window.hpp"

#include "../Event/Event_Window.hpp"
#include "../Event/Event.hpp"
#include "../Event/Event_Mouse.hpp"
#include "../Event/Event_Key.hpp"

#include "Asset.hpp"

#include "../Render/Renderer.hpp"
#include "../Scene/FlyCamera.hpp"


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

		Asset::Init();

		

	}


	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<EventWindowClose>(BIND_FN(Application::OnWindowClose));
		dispatcher.Dispatch<EventWindowResize>(BIND_FN(Application::OnWindowResize));
		dispatcher.Dispatch<EventMouseMoved>(BIND_FN(Application::OnWindowMouseMoved));
		dispatcher.Dispatch<EventKey>(BIND_FN(Application::OnWindowKey));

		// TODO: 处理其它类型事件

	}


	bool Application::OnWindowClose(EventWindowClose&)
	{
		m_Running = false;
		return true;
	}


	bool Application::OnWindowResize(EventWindowResize& e)
	{
		m_Renderer->SetRenderSize(e.GetWidth(), e.GetHeight());
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		return false;
	}

	bool Application::OnWindowKey(EventKey &e)
	{
		if (e.GetKey() >= 0 && e.GetKey() < 1024)
		{
			if (e.GetAction() == GLFW_PRESS)
				e.keysPressed[e.GetKey()] = true;
			else if (e.GetAction() == GLFW_RELEASE)
			{
				e.keysPressed[e.GetKey()] = false;
				e.keysActive[e.GetKey()] = false;
			}
		}
		// TODO: 加入其它控制
	}

	bool Application::OnWindowMouseMoved(EventMouseMoved& e)
	{
		
		if (e.firstMouse)
		{
			e.lastX = e.GetX();
			e.lastY = e.GetY();
			e.firstMouse = false;
		}

		float xoffset = e.GetX() - e.lastX;
		float yoffset = e.lastY -e.GetY();  

		e.lastX = e.GetX();
		e.lastY = e.GetY();

	/*	 LOG_TRACE("({0},{1})",e.GetX(),e.GetY());
		 LOG_TRACE("static X Y: ({0},{1})",e.lastX,e.lastY);
	     LOG_TRACE("offset X Y: ({0},{1})",xoffset,yoffset);
	*/
		m_Renderer->m_Camera->InputMouse(xoffset, yoffset);
		return true;
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