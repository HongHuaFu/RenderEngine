#ifndef ENGINE_SCENE_NODE_HPP
#define ENGINE_SCENE_NODE_HPP

#include <vector>
#include <glm/glm.hpp>

namespace Engine
{
	class Mesh;
	class Material;

	class SceneNode
	{
	public:
		// ÿ���ڵ��Ӧ����Ⱦ״̬
		Mesh* Mesh;
		Material* Material;

		// bounding box 
		glm::vec3 BoxMin = glm::vec3(-99999.0f);
		glm::vec3 BoxMax = glm::vec3( 99999.0f);

	private:
		std::vector<SceneNode*> m_Children;
		SceneNode *m_Parent;


		glm::mat4 m_Transform;
		glm::mat4 m_PrevTransform; // ���׽ڵ�Transform
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec4 m_Rotation;  // .w��������ת�Ƕ�ֵ
		glm::vec3 m_Scale = glm::vec3(1.0f);

		// ��ǵ�ǰ�ڵ��Ƿ���Ҫ����
		bool m_Dirty;

		// �ڵ�ID
		unsigned int m_ID;

		// �ڵ�����
		static unsigned int CounterID;
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

		// scene graph 
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

#endif // !ENGINE_SCENE_NODE_HPP
