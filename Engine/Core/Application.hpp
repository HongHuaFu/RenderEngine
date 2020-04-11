#ifndef ENGINE_APPLICATION_HPP
#define ENGINE_APPLICATION_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "../UI/UI.hpp"

int main();

namespace Engine
{
	class Window;
	class Event;
	class WindowCloseEvent;
	class WindowResizeEvent;
	class Renderer;
	class RenderTarget;
	class UI;

	class Application
	{
	public: // ����

		// �¼�����
		virtual void EventWindowResize(WindowResizeEvent&){ }
		virtual void EventWindowClose(WindowCloseEvent&){ }

		
		virtual void EventStart(){ }  // ��Ϸѭ����ʼǰ����һ�Σ�����Unity��Start����
		virtual void EventUpdate(){ } // ÿ֡���µ���һ��
		virtual void EventDrawUI(){ } // ����UI�¼�
		virtual void EventDrawScene(unsigned int width,unsigned int height,RenderTarget* rt){ } //���Ƴ���

	public:
		Application(unsigned int window_width = 1024,
					unsigned int window_height = 720,
					const char* title = "OpenGL App");

		virtual ~Application();
		
		static Application* s_Instance;

	private:
		bool OnWindowClose(WindowCloseEvent&);
		bool OnWindowResize(WindowResizeEvent&);
		void Run();
		void OnEvent(Event&);
		void DrawScene(RenderTarget* rt);


	protected:
		UI* m_UI;
		Window* m_Window;
		Renderer* m_Renderer;
		bool m_Running = true;
		bool m_Minimized = false;
		RenderTarget* m_SceneRT;
		
		friend int ::main();
	};



	Application* CreateApplication();
}

#endif 
