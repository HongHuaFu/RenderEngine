#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace RE
{
	class Mesh;
	class Material;

	// 场景节点 以场景树的形式存储
	class SceneNode
	{
	public:
		Mesh* Mesh; // 每个节点仅有一个Mesh
		Material* Material; // 每个节点仅有一个材质(默认材质)

		// 该节点的BBox
		glm::vec3 BoxMin = glm::vec3(-99999.0f);
		glm::vec3 BoxMax = glm::vec3( 99999.0f);

	private:
		std::vector<SceneNode*> m_Children; // 该节点的所有子节点
		SceneNode *m_Parent; // 节点的父节点


		glm::mat4 m_Transform = glm::mat4(1.0f);	// 该节点的model矩阵
		glm::mat4 m_PrevTransform = glm::mat4(1.0f); // 上一次的model矩阵 用于计算速度方向

		glm::vec3 m_Position = glm::vec3(0.0f); // 位移量

		// .xyz 分量是旋转轴 .w分量是旋转角 
		glm::vec4 m_Rotation;  // 旋转量
		glm::vec3 m_Scale = glm::vec3(1.0f); // 缩放量

		// 标记当前节点是否需要更新
		bool m_Dirty;

		// 当前节点的ID
		unsigned int m_ID;
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


