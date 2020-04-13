#pragma once

#include <vector>

namespace RE
{
	class Mesh;
	class Material;
	class SceneNode;

	// ������
	// �������еĳ����ڵ㶼�ᱻ������Ⱦ
	// ��������Ⱦ�ֿ�
	// ���е���Ⱦָ�ѹ��һ����Ⱦջ��
	class Scene 
	{
	public:
		static SceneNode* Root; // �����ĸ��ڵ�
		static unsigned int CounterID; // �����ڵ����
	public:
		static void Clear();

		static SceneNode* MakeSceneNode();
		static SceneNode* MakeSceneNode(Mesh* mesh, Material* material);
		static SceneNode* MakeSceneNode(SceneNode* node);
		static void DeleteSceneNode(SceneNode* node);
	};
}

