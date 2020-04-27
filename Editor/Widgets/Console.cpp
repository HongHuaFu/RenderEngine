#include "Console.hpp"

#include <string>
#include <windows.h>
#include <tchar.h>

#ifdef max
#undef max
#endif // max

#ifdef ERROR
#undef ERROR
#endif // max

namespace Widgets
{
	std::shared_ptr<EditorLogger> Console::m_Logger = nullptr;

	Console::Console()
	{
		m_WidgetTitle = u8"控制台";
		m_Logger = std::make_shared<EditorLogger>();
	}

	void Widgets::Console::Tick()
	{
		if(m_Visible)
		{
			m_Logger->Draw();
		}
		
	}

	void EditorLogger::Clear()
	{
		m_Buf.clear();
		m_LineOffsets.clear();
		m_LineOffsets.push_back(0);
		m_TypesLayout.clear();

		for(size_t i = 0; i<3; i++)
		{
			m_LogTypeCount[i] = 0;
			m_LogTypeVisibility[i] = true;
			m_LogTypeMaxWidth[i] = 0;
		}
		
	}

	void EditorLogger::Draw()
	{
		// Options menu
		if (ImGui::BeginPopup("options"))
		{
			ImGui::Checkbox(u8"消息自动下拉", &m_AutoScroll);
			ImGui::EndPopup();
		}

		// Main window
		if (ImGui::Button(u8"设置"))
			ImGui::OpenPopup("options");
		ImGui::SameLine();

		bool clear = ImGui::Button(u8"清除");
		ImGui::SameLine();

		if (clear)
			Clear();

		ImGui::Text(u8" 显示的日志类型:");
		ImGui::SameLine();

		const auto button_log_type_visibility_toggle = [this](std::string typeName,Log_Type index)
		{
			bool& visibility = m_LogTypeVisibility[static_cast<int>(index)];

			ImGui::PushStyleColor(ImGuiCol_Button, visibility ? ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] : ImGui::GetStyle().Colors[ImGuiCol_FrameBg]);

			if (ImGui::Button(typeName.c_str()))
			{
				visibility = !visibility;
			}

			ImGui::PopStyleColor();
			ImGui::SameLine();

			ImGui::Text("%d", m_LogTypeCount[static_cast<int>(index)]);
			ImGui::SameLine();
		};

		button_log_type_visibility_toggle(u8"信息", Log_Type::INFO);
		button_log_type_visibility_toggle(u8"警告", Log_Type::WARN);
		button_log_type_visibility_toggle(u8"错误", Log_Type::ERROR);

		m_Filter.Draw(u8"关键字匹配", -100.0f);

		ImGui::Separator();
		static std::string m_log_selected;

		if(ImGui::BeginChild("scrolling",ImVec2(0,0),false,ImGuiWindowFlags_HorizontalScrollbar))
		{
			const char* buf = m_Buf.begin();
			const char* buf_end = m_Buf.end();

			ImVec4 color_odd = ImGui::GetStyle().Colors[ImGuiCol_FrameBg];
			ImVec4 color_even = color_odd; color_even.w = 0;

			float max_log_width = 0;
			max_log_width = m_LogTypeVisibility[0] ?std::max(max_log_width, m_LogTypeMaxWidth[0]) : max_log_width;
			max_log_width = m_LogTypeVisibility[1] ? std::max(max_log_width, m_LogTypeMaxWidth[1]) : max_log_width;
			max_log_width = m_LogTypeVisibility[2] ? std::max(max_log_width, m_LogTypeMaxWidth[2]) : max_log_width;
			max_log_width = std::max(max_log_width, ImGui::GetWindowContentRegionWidth());

			ImGui::PushItemWidth(max_log_width);

			for (int line_no = 0; line_no < m_LineOffsets.Size; line_no++)
			{
				const char* line_start = buf + m_LineOffsets[line_no];
				const char* line_end = (line_no + 1 < m_LineOffsets.Size) ? (buf + m_LineOffsets[line_no + 1] - 1) : buf_end;

				if(m_Filter.PassFilter(line_start,line_end) && line_no < m_TypesLayout.size())
				{
					auto type = static_cast<int>(m_TypesLayout[line_no]);
					if(m_LogTypeVisibility[type])
					{
						ImGui::BeginGroup();
						{
							// 文本颜色
							int a = 1;
							ImGui::PushStyleColor(ImGuiCol_Text, m_LogTypeColor[type]);      

							// 背景颜色
							ImGui::PushStyleColor(ImGuiCol_FrameBg, line_no % 2 != 0 ? color_odd : color_even);   

							std::string text = std::string(line_start,line_end);
							char* dummy_str = text.data();
							ImGui::InputText("##log", dummy_str, IM_ARRAYSIZE(dummy_str), ImGuiInputTextFlags_ReadOnly);
							ImGui::PopStyleColor(2);

							ImGui::EndGroup();

							// Trigger context menu
							if (ImGui::IsMouseClicked(1) && ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly))
							{
								m_log_selected = text;
								ImGui::OpenPopup("##ConsoleContextMenu");
							}
						}
					}
				}
			}

			ImGui::PopItemWidth();
		}



		if (m_AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);


		if (ImGui::BeginPopup("##ConsoleContextMenu"))
		{
			if (ImGui::MenuItem(u8"复制"))
			{
				ImGui::LogToClipboard();
				ImGui::LogText("%s", m_log_selected.c_str());
				ImGui::LogFinish();
			}

			ImGui::Separator();

			if (ImGui::MenuItem(u8"查找"))
			{
				auto address = "https://www.bing.com/search?q=" + m_log_selected;

				ShellExecute(NULL, NULL,address.c_str(), NULL, NULL, SW_SHOWNORMAL);
			}

			ImGui::EndPopup();
		}

		ImGui::EndChild();
	}
}


