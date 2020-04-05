#ifndef ENGINE_APPLICATION_HPP
#define ENGINE_APPLICATION_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

int main();

namespace Engine
{
	class Window;
	class Event;
	class WindowCloseEvent;
	class WindowResizeEvent;

	class Application
	{
	public: // 重载

		// 事件重载
		virtual void EventWindowResize(WindowResizeEvent&){ }
		virtual void EventWindowClose(WindowCloseEvent&){ }

		
		virtual void EventStart(){ }  // 游戏循环开始前调用一次，类似Unity的Start函数
		virtual void EventUpdate(){ } // 每帧更新调用一次

	public:
		Application(unsigned int window_width = 1024,
					unsigned int window_height = 720,
					const char* title = "OpenGL App");

		virtual ~Application();
		
		

	private:
		bool OnWindowClose(WindowCloseEvent&);
		bool OnWindowResize(WindowResizeEvent&);
		void Run();
		void OnEvent(Event&);

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
