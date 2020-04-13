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

		// ���ָ��ڵ�ǿ�
		Scene::Root = new SceneNode(0);
	}

	// �����սڵ�
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

	// ���ƽڵ�
	SceneNode* Scene::MakeSceneNode(SceneNode* node)
	{
		SceneNode* newNode = new SceneNode(Scene::CounterID++);

		newNode->Mesh     = node->Mesh;
		newNode->Material = node->Material;
		newNode->BoxMin   = node->BoxMin;
		newNode->BoxMax   = node->BoxMax;

		// ����ǰ�ڵ�������ӽڵ�һһѹ��ջ��
		std::stack<SceneNode*> nodeStack;
		for (unsigned int i = 0; i < node->GetChildCount(); ++i)
			nodeStack.push(node->GetChildByIndex(i));

		// TODO: δ���������� ����������
		while (!nodeStack.empty())
		{
			SceneNode* child = nodeStack.top();
			nodeStack.pop();

			// ��ʱ�ڵ�
			SceneNode* newChild = new SceneNode(Scene::CounterID++);
			newChild->Mesh     = child->Mesh;
			newChild->Material = child->Material;
			newChild->BoxMin   = child->BoxMin;
			newChild->BoxMax   = child->BoxMax;
			newNode->AddChild(newChild);

			// ���ӽڵ�������ӽڵ�һһѹ��ջ��
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

		// �����ڵ����������������������ӽڵ㲢������һһ�ͷ�
		delete node;
	}
}