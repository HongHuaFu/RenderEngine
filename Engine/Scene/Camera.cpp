#include "Camera.hpp"
#include "../Math/Math.hpp"
#include <glm/ext.hpp>

namespace Engine
{
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
		Frustum.Update(this);
	}

	void Camera::SetPerspective(float fov, float aspect, float near, float far)
	{
		Perspective = true;
		Projection = glm::perspective(fov, aspect, near, far);
		FOV    = fov;
		Aspect = aspect;
		Near   = near;
		Far    = far;
	}
	
	// TODO: 修改正交投影矩阵
	void Camera::SetOrthographic(float left, float right, float top, float bottom, float near, float far)
	{
		Perspective = false;
		Projection = glm::orthoLH(left, right, bottom,top, near, far);
		Near = near;
		Far  = far;
	}
	

	void Camera::UpdateView()
	{
		View = glm::lookAt(Position, Position + Forward, Up);
	}
	

	float Camera::FrustumHeightAtDistance(float distance)
	{
		if (Perspective)
		{
			return 2.0f * distance * tanf(Math::Deg2Rad(FOV * 0.5));
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
			return frustumHeight * 0.5f / tanf(Math::Deg2Rad(FOV * 0.5f));
		}
		else
		{
			return Frustum.Near.D;
		}
	}
}