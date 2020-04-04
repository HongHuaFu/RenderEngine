#ifndef ENGINE_WINDOW_HPP
#define ENGINE_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include "../Event/Event.hpp"

namespace Engine
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "OpenGL Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	private:
		using EventCallbackFn = std::function<void(Event&)>;

		GLFWwindow* m_WindowPtr;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	public:
		 Window(const WindowProps&);
		~Window();
		void OnUpdate();

	public: // setter
		inline void SetEventCallback(const EventCallbackFn& callback)
		{ 
			m_Data.EventCallback = callback; 
		}

		void SetVSync(bool enabled);

	public: // getter
		inline bool IsVSync() const { return m_Data.VSync; }

		inline unsigned int GetWidth()  const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }

		inline void* GetNativeWindow() const { return m_WindowPtr; }
	};

}



#endif 
