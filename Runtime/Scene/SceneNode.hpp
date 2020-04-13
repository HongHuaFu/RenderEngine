#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace RE
{
	class Mesh;
	class Material;

	// �����ڵ� �Գ���������ʽ�洢
	class SceneNode
	{
	public:
		Mesh* Mesh; // ÿ���ڵ����һ��Mesh
		Material* Material; // ÿ���ڵ����һ������(Ĭ�ϲ���)

		// �ýڵ��BBox
		glm::vec3 BoxMin = glm::vec3(-99999.0f);
		glm::vec3 BoxMax = glm::vec3( 99999.0f);

	private:
		std::vector<SceneNode*> m_Children; // �ýڵ�������ӽڵ�
		SceneNode *m_Parent; // �ڵ�ĸ��ڵ�


		glm::mat4 m_Transform = glm::mat4(1.0f);	// �ýڵ��model����
		glm::mat4 m_PrevTransform = glm::mat4(1.0f); // ��һ�ε�model���� ���ڼ����ٶȷ���

		glm::vec3 m_Position = glm::vec3(0.0f); // λ����

		// .xyz ��������ת�� .w��������ת�� 
		glm::vec4 m_Rotation;  // ��ת��
		glm::vec3 m_Scale = glm::vec3(1.0f); // ������

		// ��ǵ�ǰ�ڵ��Ƿ���Ҫ����
		bool m_Dirty;

		// ��ǰ�ڵ��ID
		unsigned int m_ID;
	public:
		SceneNode(unsigned int id);
		~SceneNode();

		// �����ڵ� transform
		void SetPosition(glm::vec3 position);
		void SetRotation(glm::vec4 rotation);
		void SetScale(glm::vec3 scale);
		void SetScale(float scale);
		glm::vec3 GetLocalPosition();
		glm::vec4 GetLocalRotation();
		glm::vec3 GetLocalScale();
		glm::vec3 GetWorldPosition();
		glm::vec3 GetWorldScale();

		unsigned int GetID();
		void AddChild(SceneNode *node);
		void RemoveChild(unsigned int id); 
		std::vector<SceneNode*> GetChildren();
		unsigned int GetChildCount();
		SceneNode* GetChild(unsigned int id);
		SceneNode* GetChildByIndex(unsigned int index);
		SceneNode* GetParent();

		glm::mat4 GetTransform();
		glm::mat4 GetPrevTransform();

		// ���µ�ǰ�ڵ㼰�����ӽڵ�
		void UpdateTransform(bool updatePrevTransform = false);
	};
}


