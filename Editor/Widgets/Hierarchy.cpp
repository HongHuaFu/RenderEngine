#include "Hierarchy.hpp"
#include <Api.hpp>

Hierarchy::Hierarchy()
{
	m_WidgetTitle = u8"世界树";
	m_ImguiFlag |= ImGuiWindowFlags_HorizontalScrollbar;
}

void Hierarchy::Tick()
{
	// 绘制场景物体树
	TreeShow();
}

void TreeAddNode(RE::SceneNode* node)
{
	if(!node)
		return;

	auto sons = node->GetChildren();
	ImGuiTreeNodeFlags node_flags	= ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth;
	node_flags |= sons.size() > 0 ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Leaf;
	

	const auto is_node_open = ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<intptr_t>(node->GetID())), node_flags, node->name.c_str());

	// 递归显示子物体
	if (is_node_open)
	{
		if (sons.size() > 0)
		{
			for (const auto& child : sons)
			{
				auto childSons = child->GetChildren();
				if (childSons.size() == 0)
					continue;
				for(const auto& childSon:childSons)
				{
					TreeAddNode(childSon);
				}
			}
		}

		ImGui::TreePop();
	}
}


void Hierarchy::TreeShow()
{
	if (ImGui::TreeNodeEx(u8"树根", ImGuiTreeNodeFlags_DefaultOpen))
	{
		auto rootSons = RE::Scene::Root->GetChildren();
		for (const auto& son : rootSons)
		{
			TreeAddNode(son);
		}
		
		ImGui::TreePop();
	}
}

