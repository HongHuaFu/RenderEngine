#include "Scene.hpp"
#include "SceneNode.hpp"

#include <stack>

namespace RE
{
	SceneNode* Scene::Root = new SceneNode(0);
	unsigned int Scene::CounterID = 0;    

	void Scene::Clear()
	{       
		Scene::DeleteSceneNode(Root);

		// 保持根节点非空
		Scene::Root = new SceneNode(0);
	}

	// 创建空节点
	SceneNode* Scene::MakeSceneNode()
	{
		SceneNode* node = new SceneNode(Scene::CounterID++);
		Root->AddChild(node);
		return node;
	}


	SceneNode* Scene::MakeSceneNode(Mesh* mesh, Material* material)
	{
		SceneNode* node = new SceneNode(Scene::CounterID++);

		node->Mesh = mesh;
		node->Material = material;

		Root->AddChild(node);
		return node;
	}

	// 复制节点
	SceneNode* Scene::MakeSceneNode(SceneNode* node)
	{
		SceneNode* newNode = new SceneNode(Scene::CounterID++);

		newNode->Mesh     = node->Mesh;
		newNode->Material = node->Material;
		newNode->BoxMin   = node->BoxMin;
		newNode->BoxMax   = node->BoxMax;

		// 将当前节点的所有子节点一一压入栈中
		std::stack<SceneNode*> nodeStack;
		for (unsigned int i = 0; i < node->GetChildCount(); ++i)
			nodeStack.push(node->GetChildByIndex(i));

		// TODO: 未能完整复制 二叉树复制
		while (!nodeStack.empty())
		{
			SceneNode* child = nodeStack.top();
			nodeStack.pop();

			// 临时节点
			SceneNode* newChild = new SceneNode(Scene::CounterID++);
			newChild->Mesh     = child->Mesh;
			newChild->Material = child->Material;
			newChild->BoxMin   = child->BoxMin;
			newChild->BoxMax   = child->BoxMax;
			newNode->AddChild(newChild);

			// 将子节点的所有子节点一一压入栈中
			for (unsigned int i = 0; i < child->GetChildCount(); ++i)
				nodeStack.push(child->GetChildByIndex(i));
		}

		Root->AddChild(newNode);
		return newNode;
	}


	void Scene::DeleteSceneNode(SceneNode* node)
	{
		if (node->GetParent())
		{
			node->GetParent()->RemoveChild(node->GetID());
		}

		// 场景节点的析构函数将会遍历所有子节点并将它们一一释放
		delete node;
	}
}