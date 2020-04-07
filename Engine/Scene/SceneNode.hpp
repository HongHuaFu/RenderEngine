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
		// 每个节点对应的渲染状态
		Mesh* Mesh;
		Material* Material;

		// bounding box 
		glm::vec3 BoxMin = glm::vec3(-99999.0f);
		glm::vec3 BoxMax = glm::vec3( 99999.0f);

	private:
		std::vector<SceneNode*> m_Children;
		SceneNode *m_Parent;


		glm::mat4 m_Transform;
		glm::mat4 m_PrevTransform; // 父亲节点Transform
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec4 m_Rotation;  // .w分量是旋转角度值
		glm::vec3 m_Scale = glm::vec3(1.0f);

		// 标记当前节点是否需要更新
		bool m_Dirty;

		// 节点ID
		unsigned int m_ID;

		// 节点总数
		static unsigned int CounterID;
	public:
		SceneNode(unsigned int id);
		~SceneNode();

		// 场景节点 transform
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

		// 更新当前节点及它的子节点
		void UpdateTransform(bool updatePrevTransform = false);
	};
}

#endif // !ENGINE_SCENE_NODE_HPP
