#include "UI.hpp"
#include "UIStyle.hpp"
#include "UILayout.hpp"
#include "../Core/Application.hpp"


namespace Engine
{
	
	void UI::UIStart()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool popen = true;
		UILayout::ShowMainMenu(&popen);

		// FileBrowser

		UIFileBrowser::drawGui();
	}

	void UI::UIEnd()
	{
		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize((GLFWwindow*)m_Window->GetNativeWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}


	bool UI::Init(Window* w)
	{
		m_Window = w;
		
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;      
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;          
		UIStyle::PSStyle();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_Window->GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 430");

		// TODO: 使用自定义资源路径
		ImFont* font = io.Fonts->AddFontFromFileTTF("fonts/consola.ttf", 14.0f);
		IM_ASSERT(font != NULL);

		

		return true;
	}

	void UI::Clean()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

}

