#ifndef ENGINE_SCENE_HPP
#define ENGINE_SCENE_HPP

#include <vector>

namespace Engine
{
	class Mesh;
	class Material;
	class SceneNode;

	// 主场景
	class Scene 
	{
	public:
		static SceneNode* Root; // 根节点
		static unsigned int CounterID;
	public:
		static void Clear();

		static SceneNode* MakeSceneNode();
		static SceneNode* MakeSceneNode(Mesh* mesh, Material* material);
		static SceneNode* MakeSceneNode(SceneNode* node);
		static void DeleteSceneNode(SceneNode* node);
	};
}

#endif // !ENGINE_SCENE_HPP
