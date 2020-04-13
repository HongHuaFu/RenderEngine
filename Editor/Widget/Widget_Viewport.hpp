#pragma once

#include <Api.hpp>
#include "../ImGui/imgui.h"

static void Widget_Viewport(RE::Texture* tex)
{
	ImGui::Begin("Scene");

	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 size = ImGui::GetWindowSize();
	ImGui::GetWindowDrawList()->AddImage(
		(void *)tex->GetID(), ImVec2(pos),
		ImVec2(pos.x + size.x,pos.y + size.y), 
		ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}