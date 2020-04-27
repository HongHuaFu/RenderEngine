#include "Editor.hpp"
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "Widgets/Console.hpp"
#include "Widgets/ViewPort.hpp"
#include "Widgets/Hierarchy.hpp"
#include "Style.hpp"
#include <Api.hpp>

using namespace RE;
using namespace Widgets;

Editor::~Editor()
{
	m_Widgets.clear();
	m_Widgets.shrink_to_fit();
	ImGUIClose();
}

void Editor::OnStart(GLFWwindow* window,Renderer* renderer)
{
	m_Renderer = renderer;
	m_Window = window;
	ImGUIInit();
	Create_Widgets();
}

void Editor::OnTick()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	OnTick_Widgets();
}

void Editor::PushRender()
{
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void Editor::Create_Widgets()
{
	m_Widgets.emplace_back(std::make_unique<Console>());
	m_Widgets.emplace_back(std::make_unique<ViewPort>(m_Renderer));
	m_Widgets.emplace_back(std::make_unique<Hierarchy>());
}

void Editor::OnTick_Widgets()
{
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		BeginMainWindow();
	}

	for (auto& widget : m_Widgets)
	{
		widget->Begin();
		widget->Tick();
		widget->End();
	}

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		EndMainWindow();
	}
}

void Editor::BeginMainWindow()
{
	const auto window_flags =
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove  |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus;

	// Set window position and size
	float offset_y  = 0;
	offset_y += 0;
	offset_y += 0;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + offset_y));
	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - offset_y));
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowBgAlpha(0.0f);

	// Begin window
	bool open = true;
	m_EditorBegin = ImGui::Begin(m_EditorName.c_str(), &open, window_flags);
	ImGui::PopStyleVar(3);

	// Begin dock space
	if (m_EditorBegin)
	{
		// Dock space
		const auto window_id = ImGui::GetID(m_EditorName.c_str());
		if (!ImGui::DockBuilderGetNode(window_id))
		{
			// Reset current docking state
			ImGui::DockBuilderRemoveNode(window_id);
			ImGui::DockBuilderAddNode(window_id, ImGuiDockNodeFlags_None);
			ImGui::DockBuilderSetNodeSize(window_id, ImGui::GetMainViewport()->Size);

			// DockBuilderSplitNode(ImGuiID node_id, ImGuiDir split_dir, float size_ratio_for_node_at_dir, ImGuiID* out_id_dir, ImGuiID* out_id_other);
			ImGuiID dock_main_id = window_id;
			ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id,		ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
			const ImGuiID dock_right_down_id = ImGui::DockBuilderSplitNode(dock_right_id,	ImGuiDir_Down,	0.6f, nullptr, &dock_right_id);
			ImGuiID dock_down_id = ImGui::DockBuilderSplitNode(dock_main_id,		ImGuiDir_Down,	0.25f,  nullptr, &dock_main_id);
			const ImGuiID dock_down_right_id = ImGui::DockBuilderSplitNode(dock_down_id,		ImGuiDir_Right, 0.6f,   nullptr, &dock_down_id);

			// Dock windows	
			ImGui::DockBuilderDockWindow("World", dock_right_id);
			ImGui::DockBuilderDockWindow("Properties", dock_right_down_id);
			ImGui::DockBuilderDockWindow(u8"控制台",	dock_down_id);
			ImGui::DockBuilderDockWindow("Assets", dock_down_right_id);
			ImGui::DockBuilderDockWindow(u8"场景图", dock_main_id);
			ImGui::DockBuilderFinish(dock_main_id);
		}

		ImGui::DockSpace(window_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
	}
}

void Editor::EndMainWindow()
{
	if (m_EditorBegin)
	{
		ImGui::End();
	}
}

void Editor::ImGUIInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  

	// Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 

	// Enable Multi-Viewport 
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  

	io.ConfigWindowsResizeFromEdges = true;
	io.ConfigViewportsNoTaskBarIcon = true;

	// style设置
	Style::Dark();

	// 事件绑定
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 460");


	ImFont* font = io.Fonts->AddFontFromFileTTF("Asset/Font/SIMYOU.TTF", 12.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	IM_ASSERT(font != NULL);
}

void Editor::ImGUIClose()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
