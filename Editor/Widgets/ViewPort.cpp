#include "ViewPort.hpp"
#include <glm/glm.hpp>
#include <Api.hpp>
#include "../ImGui/imgui_internal.h"
#include "Console.hpp"

using namespace std;
using namespace RE;


ViewPort::ViewPort(Renderer* renderer)
{
	m_WidgetTitle = u8"����ͼ";
	m_WidgetSize = ImVec2(400, 250);
	m_ImguiFlag |= ImGuiWindowFlags_NoScrollbar;
	m_ImguiFlag |= ImGuiWindowFlags_NoScrollWithMouse;
	m_WidgetPadding = ImVec2(4.0f,4.0f);

	m_Renderer = renderer;
}

void ViewPort::Tick()
{
	if(!m_Visible)
		return;

	if (!m_Renderer)
		return;

	// ��ȡ��ǰ���ڴ�С
	uint32_t width = static_cast<uint32_t>(ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x);
	uint32_t height	= static_cast<uint32_t>(ImGui::GetWindowContentRegionMax().y - ImGui::GetWindowContentRegionMin().y);

	// ���ڿ��Ϊ2�ı���
	width -= (width	% 2 != 0) ? 1 : 0;
	height -= (height % 2 != 0) ? 1 : 0;

	// ������Ⱦ���ӿ�
	if (m_Renderer->m_RenderSize.x != width || m_Renderer->m_RenderSize.y != height)
	{
		m_Renderer->SetRenderSize(width,height);
	}

	auto id = m_Renderer->m_CustomTarget->GetColorTexture(0)->GetID();
	// ��������ͼƬ��
	ImGui::Image(
		(ImTextureID)(id),
		ImVec2(static_cast<float>(width), static_cast<float>(height)),
		ImVec2(0, 1), ImVec2(1, 0),
		ImColor(255, 255, 255, 255),
		ImColor(50, 127, 166, 255)
	);

}
