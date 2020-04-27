#pragma once

#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"

#include <functional>
#include <string>


class Widget
{
private:
	// PushStyleVar 数据栈计数器
	unsigned int m_PushCounter{ 0 };

	bool m_BeginSucceed{ false };

protected:
	bool m_Visible{ true };
	bool m_IsWindow{ true };
	float m_Alpha{ -1.0f };
	float m_Height{ 0 };

	std::string m_WidgetTitle{ };
	int m_ImguiFlag = ImGuiWindowFlags_NoCollapse; 

	ImGuiWindow* m_Window{ nullptr};


	ImVec2 m_WidgetPos { -1.0f,-1.0f };
	ImVec2 m_WidgetSize { -1.0f,-1.0f };
	ImVec2 m_WidgetSizeMax { 999999.0f,999999.0f };
	ImVec2 m_WidgetPadding { -1.0f,-1.0f };

protected:
	std::function<void()> m_EventOnStart{ nullptr };
	std::function<void()> m_EventOnVisible{ nullptr };
	std::function<void()> m_EventOnBegin{ nullptr };
	
public:
	Widget() = default;

	virtual ~Widget() = default;
	virtual void Tick() = 0;
	bool Begin();
	bool End();

	// 额外的自定义Style设置
	template<typename T>
	inline void PushStyleVar(ImGuiStyleVar idx, T val) 
	{ 
		ImGui::PushStyleVar(idx, val); 
		m_PushCounter++; 
	}

	inline bool IsWindow() const { return m_IsWindow; }
	inline bool& IsVisible() { return m_Visible; }
	inline void SetVisible(bool is_visible) { m_Visible = is_visible; }
	inline float GetHeight() const { return m_Height; }
	inline ImGuiWindow* GetWindow() const { return m_Window; }
	inline const auto& GetTitle() const { return m_WidgetTitle; }
};