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
	class EventMouseMoved;
	class EventKey;
	class Renderer;
	class RenderTarget;

	class Application
	{
	public:
		virtual void OnStart(){ } // ѭ����ʼǰ����һ��
		virtual void OnUpdate(){ } // ÿ֡����һ��

	public:
		Application(unsigned int window_width = 1024,unsigned int window_height = 720,const char* title = "OpenGL App");

		virtual ~Application();

	private:
		// �����¼�
		bool OnWindowClose(EventWindowClose&);
		bool OnWindowResize(EventWindowResize&);
		bool OnWindowMouseMoved(EventMouseMoved&);
		bool OnWindowKey(EventKey&);

		void Run();

		// �¼�����
		void OnEvent(Event&);

	protected:
		Window* m_Window;
		Renderer* m_Renderer;

		bool m_Running = true;
		bool m_Minimized = false;


	public:
		friend int ::main();
	};

	Application* CreateApplication();
}

