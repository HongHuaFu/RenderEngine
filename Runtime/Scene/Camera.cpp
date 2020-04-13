#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace RE
{
	// 更新Camera的视锥体
	void CameraFrustum::Update(Camera* camera)
	{
		float tan = 2.0 * std::tan(camera->FOV * 0.5);
		float nearHeight = tan * camera->Near;
		float nearWidth = nearHeight * camera->Aspect;
		float farHeight = tan * camera->Far;
		float farWidth = farHeight * camera->Aspect;

		// 计算近/远平面的中心点
		glm::vec3 nearCenter = camera->Position + camera->Forward * camera->Near;
		glm::vec3 farCenter = camera->Position + camera->Forward * camera->Far;

		glm::vec3 v;

		// 1.构造左平面
		v = (nearCenter - camera->Right * nearWidth * 0.5f) - camera->Position;
		Left.SetNormalD(glm::cross(glm::normalize(v), camera->Up), nearCenter - camera->Right * nearWidth * 0.5f);

		// 2.构造右平面
		v = (nearCenter + camera->Right * nearWidth  * 0.5f) - camera->Position;
		Right.SetNormalD(glm::cross(camera->Up, glm::normalize(v)), nearCenter + camera->Right * nearWidth * 0.5f);


		// 3.构造顶面
		v = (nearCenter + camera->Up * nearHeight * 0.5f) - camera->Position;
		Top.SetNormalD(glm::cross(glm::normalize(v), camera->Right), nearCenter + camera->Up * nearHeight * 0.5f);

		// 4.构造底面
		v = (nearCenter - camera->Up * nearHeight * 0.5f) - camera->Position;
		Bottom.SetNormalD(glm::cross(camera->Right, glm::normalize(v)), nearCenter - camera->Up * nearHeight * 0.5f);

		// 5.构造近平面
		Near.SetNormalD(camera->Forward, nearCenter);
		// 6.构造远平面
		Far.SetNormalD(-camera->Forward, farCenter);
	}


	bool CameraFrustum::Intersect(glm::vec3 point)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (Planes[i].Distance(point) < 0)
			{
				return false;
			}
		}
		return true;
	}

	bool CameraFrustum::Intersect(glm::vec3 point,float radius)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (Planes[i].Distance(point) < -radius)
			{
				return false;
			}
		}
		return true;
	}

	bool CameraFrustum::Intersect(glm::vec3 boxMin,glm::vec3 boxMax)
	{
		for (int i = 0; i < 6; ++i)
		{
			glm::vec3 positive = boxMin;
			if (Planes[i].Normal.x >= 0)
			{
				positive.x = boxMax.x;
			}
			if (Planes[i].Normal.y >= 0)
			{
				positive.y = boxMax.y;
			}
			if (Planes[i].Normal.z >= 0)
			{
				positive.z = boxMax.z;
			}
			if(Planes[i].Distance(positive) < 0)
			{
				return false;
			}
		}
		return true;
	}


	Camera::Camera()
	{

	}

	Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up)
	: Position(position), Forward(forward), Up(up)
	{
		UpdateView();
	}
	
	void Camera::Update(float dt)
	{
		// 更新视锥体
		Frustum.Update(this);
	}

	void Camera::SetPerspective(float fovy, float aspect, float near, float far)
	{
		Perspective = true;
		Projection = glm::perspective(fovy, aspect, near, far);
		FOV = fovy;
		Aspect = aspect;
		Near = near;
		Far = far;
	}

	void Camera::SetOrthographic(float left, float right, float top, float bottom, float near, float far)
	{
		Perspective = false;
		Projection = glm::ortho(left, right, bottom,top, near, far);
		Near = near;
		Far = far;
	}

	void Camera::UpdateView()
	{
		View = glm::lookAt(Position, Position + Forward, Up);
	}

	float Camera::FrustumHeightAtDistance(float distance)
	{
		if (Perspective)
		{
			return 2.0f * distance * tanf(glm::radians(FOV * 0.5f));
		}
		else
		{
			return Frustum.Top.D;
		}
	}
	
	float Camera::DistanceAtFrustumHeight(float frustumHeight)
	{
		if (Perspective)
		{
			return frustumHeight * 0.5f / tanf(glm::radians(FOV * 0.5f));
		}
		else
		{
			return Frustum.Near.D;
		}
	}

}


