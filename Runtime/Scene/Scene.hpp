#pragma once

#include <vector>

namespace RE
{
	class Mesh;
	class Material;
	class SceneNode;

	// 主场景
	// 并非所有的场景节点都会被遍历渲染
	// 场景与渲染分开
	// 所有的渲染指令将压入一个渲染栈中
	class Scene 
	{
	public:
		static SceneNode* Root; // 场景的根节点
		static unsigned int CounterID; // 场景节点计数
	public:
		static void Clear();

		static SceneNode* MakeSceneNode();
		static SceneNode* MakeSceneNode(Mesh* mesh, Material* material);
		static SceneNode* MakeSceneNode(SceneNode* node);
		static void DeleteSceneNode(SceneNode* node);
	};
}

