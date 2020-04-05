#include "Window.hpp"
#include "Log.hpp"
#include "../Event/WindowEvent.hpp"


namespace Engine
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

		// TODO: 替换ASSERT
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
		// TODO: 替换ASSERT
		if(!m_WindowPtr)
		{
			LOG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		++s_GLFWWindowCount;

		glfwMakeContextCurrent(m_WindowPtr);

		// TODO: 替换ASSERT
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
		}

		LOG_INFO("OpenGL Info:");
		LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LOG_INFO("  Version: {0}", glGetString(GL_VERSION));


		glfwSetWindowUserPointer(m_WindowPtr, &m_Data);
		SetVSync(true);

#pragma region GLFW 回调函数区域

		glfwSetWindowSizeCallback(m_WindowPtr, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
	
			// TODO: 放置在更加合适的地方，因为可能会突然闪烁
			glViewport(0,0,width,height);
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_WindowPtr, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

#pragma endregion

		
	}


	Window::~Window()
	{
		glfwDestroyWindow(m_WindowPtr);
		--s_GLFWWindowCount;

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

