#ifndef ENGINE_UI_HPP
#define ENGINE_UI_HPP

#include "../Core/Window.hpp"
#include "../Vendor/imgui.h"
#include "../Vendor/imgui_impl_glfw.h"
#include "../Vendor/imgui_impl_opengl3.h"
#include "UIFileBrowser.hpp"

namespace Engine
{
	

	class UI
	{
	public:
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		UI(Window* w){ Init(w);}
		~UI(){ Clean(); }

		void UIStart();
		void UIEnd();

		
		
	private:
		void Clean();
		bool Init(Window* w);

		Window* m_Window;
	};
}

#endif // !ENGINE_UI_HPP
