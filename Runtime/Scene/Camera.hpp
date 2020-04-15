#pragma once

#include <glm/glm.hpp>

namespace RE
{
	// 点法式
	struct FrustumPlane
	{
		glm::vec3 Normal;
		float D;

		void SetNormalD(glm::vec3 normal, glm::vec3 point)
		{
			Normal = glm::normalize(normal);
			D = -glm::dot(Normal, point);
		}

		float Distance(glm::vec3 point)
		{
			return glm::dot(Normal, point) + D;
		}
	};

	class Camera;
	// 相机视锥体 
	// 若渲染物体的BBox与视锥体不相交，即完全位于视锥体外，则将其剔除
	// 提前剔除减少提交到GPU端的渲染命令
	class CameraFrustum
	{
	public:
		union
		{
			FrustumPlane Planes[6];
			struct
			{
				FrustumPlane Left;
				FrustumPlane Right;
				FrustumPlane Top;
				FrustumPlane Bottom;
				FrustumPlane Near;
				FrustumPlane Far;
			};
		};

	public:
		CameraFrustum() { }

		void Update(Camera* camera);

		// 点是否在视锥体内
		bool Intersect(glm::vec3 point);

		// 球体是否与视锥体相交
		bool Intersect(glm::vec3 point, float radius);

		// BBox是否与视锥体相交
		bool Intersect(glm::vec3 boxMin, glm::vec3 boxMax);
	};

	enum class CAMERA_MOVEMENT {
		FORWARD,
		BACK,
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	class Camera
	{
	public:
		glm::mat4 Projection;
		glm::mat4 View;

		glm::vec3 Position = glm::vec3(0.0f, 0.0f,  0.0f);
		glm::vec3 Forward = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f,  0.0f);
		glm::vec3 Right = glm::vec3(1.0f, 0.0f,  0.0f);

		float FOV;
		float Aspect;
		float Near;
		float Far;
		bool Perspective;

		CameraFrustum Frustum;

	public:
		Camera(); 
		Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);

		void SetPerspective(float fovy, float aspect, float near, float far);
		void SetOrthographic(float left, float right, float top, float bottom, float near, float far);

		void UpdateView();

		float FrustumHeightAtDistance(float distance);
		float DistanceAtFrustumHeight(float frustumHeight);

		virtual void Update(){ }
		virtual void Update(float dt){ }
		virtual void InputKey(float dt, CAMERA_MOVEMENT direction){ }
		virtual void InputMouse(float deltaX, float deltaY){ }
		virtual void InputScroll(float deltaX, float deltaY){ }
	};
}