#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

int main();

namespace RE
{
	class Window;
	class Event;
	class EventWindowClose;
	class EventWindowResize;
	class Renderer;
	class RenderTarget;

	class Application
	{
	public:
		virtual void OnStart(){ } // 循环开始前调用一次
		virtual void OnUpdate(){ } // 每帧调用一次

	public:
		Application(unsigned int window_width = 1024,unsigned int window_height = 720,const char* title = "OpenGL App");

		virtual ~Application();

	private:
		// 窗口事件
		bool OnWindowClose(EventWindowClose&);
		bool OnWindowResize(EventWindowResize&);

		void Run();

		// 事件调用
		void OnEvent(Event&);

	protected:
		Window* m_Window;

		bool m_Running = true;
		bool m_Minimized = false;


	public:
		friend int ::main();
	};

	Application* CreateApplication();
}

