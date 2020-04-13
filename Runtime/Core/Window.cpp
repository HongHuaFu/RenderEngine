#include "Window.hpp"
#include "Macro.hpp"

#include "../Event/Event_Window.hpp"


namespace RE
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window::Window(const WindowProps &props)
	{
		m_Data.Title  = props.Title;
		m_Data.Width  = props.Width;
		m_Data.Height = props.Height;

		LOG_TRACE("Creating window {0}, size:({1}, {2})", props.Title, props.Width, props.Height);
		if (s_GLFWWindowCount == 0)
		{
			if(!glfwInit())
			{
				LOG_ERROR("Could not intialize GLFW!");
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
			glfwWindowHint(GLFW_RESIZABLE, true);

			glfwSetErrorCallback(GLFWErrorCallback);
		}

		m_WindowPtr = glfwCreateWindow((int)props.Width, 
			(int)props.Height, 
			m_Data.Title.c_str(), 
			nullptr, nullptr);

		if(!m_WindowPtr)
		{
			LOG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		++s_GLFWWindowCount;

		glfwMakeContextCurrent(m_WindowPtr);


		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
		}

		LOG_INFO("OpenGL Info:");
		LOG_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		LOG_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		LOG_INFO("Version: {0}", glGetString(GL_VERSION));


		glfwSetWindowUserPointer(m_WindowPtr, &m_Data);
		SetVSync(true);


		// ���ûص�����
		glfwSetWindowSizeCallback(m_WindowPtr, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			// ��������������һ��vieport
			glViewport(0,0,width,height);
			EventWindowResize event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_WindowPtr, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			EventWindowClose event;
			data.EventCallback(event);
		});

	}


	Window::~Window()
	{
		glfwDestroyWindow(m_WindowPtr);
		--s_GLFWWindowCount;

		// �������һ�����ڹرպ����ֹGLFW
		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}


	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowPtr);
	}

	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
}
