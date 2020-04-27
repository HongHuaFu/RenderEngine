#include "Widget.hpp"

bool Widget::Begin()
{
	if(m_EventOnStart)
		m_EventOnStart();

	if(!m_Visible || !m_IsWindow)
		return false;

	if(m_EventOnVisible)
		m_EventOnVisible();

	// ���ڲ�������
	if (m_WidgetPos.x != -1.0f && m_WidgetPos.y != -1.0f)
	{
		ImGui::SetNextWindowPos(m_WidgetPos);
	}

	if (m_WidgetPadding.x != -1.0f && m_WidgetPadding.y != -1.0f)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, m_WidgetPadding);
		m_PushCounter++;
	}

	if (m_Alpha != -1.0f)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, m_Alpha);
		m_PushCounter++;
	}

	if (m_WidgetSize.x != -1.0f && m_WidgetSize.y != -1.0f)
	{
		ImGui::SetNextWindowSize(m_WidgetSize, ImGuiCond_FirstUseEver);
	}

	if ((m_WidgetSize.x != -1.0f && m_WidgetSize.y != -1.0f) || (m_WidgetSizeMax.x != 999999.0f && m_WidgetSizeMax.y != 999999.0f))
	{
		ImGui::SetNextWindowSizeConstraints(m_WidgetSize, m_WidgetSizeMax);
	}

	// ImGui::Begin
	if (ImGui::Begin(m_WidgetTitle.c_str(), &m_Visible, m_ImguiFlag))
	{
		m_Window = ImGui::GetCurrentWindow();
		m_Height = ImGui::GetWindowHeight();
		m_BeginSucceed = true;
	}
	else if (m_Window && m_Window->Hidden)
	{
		// ���������������

		// ����״̬�� ImGui::Begin ���ǵ�����
		m_BeginSucceed = true;
	}

	if (m_BeginSucceed && m_EventOnBegin)
	{
		m_EventOnBegin();
	}

	return m_BeginSucceed;
}

bool Widget::End()
{
	if (m_BeginSucceed)
	{
		ImGui::End();
	}

	// ����ջԪ��
	ImGui::PopStyleVar(m_PushCounter);
	m_PushCounter = 0;

	m_BeginSucceed = false;

	return true;
}
