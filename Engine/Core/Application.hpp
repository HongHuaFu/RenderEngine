#ifndef ENGINE_APPLICATION_HPP
#define ENGINE_APPLICATION_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.hpp"
#include "../Event/WindowEvent.hpp"

int main();

namespace Engine
{
	class Application
	{
	public: // 重载

		// 事件重载
		virtual void EventWindowResize(WindowResizeEvent&){ }
		virtual void EventWindowClose(WindowCloseEvent&){ }

	public:
		Application(unsigned int window_width = 1024,
					unsigned int window_height = 720,
					const char* title = "OpenGL App");

		virtual ~Application();
		void OnEvent(Event&);
		

	private:
		bool OnWindowClose(WindowCloseEvent&);
		bool OnWindowResize(WindowResizeEvent&);
		void Run();
		
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;

		static Application* s_Instance;
		friend int ::main();
	};



	Application* CreateApplication();
}

#endif 
