#pragma once

#include "Camera.hpp"

namespace RE
{
	class FlyCamera : public Camera
	{
	public:
		float Yaw;
		float Pitch;

		float MovementSpeed   = 10.0f;
		float MouseSensitivty =  0.1f;
		float Damping         =  5.0f;
	private:
		glm::vec3 m_TargetPosition;
		glm::vec3 m_WorldUp;
		float m_TargetYaw;
		float m_TargetPitch;

	public:
		FlyCamera(glm::vec3 position, glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

		virtual void Update(float dt);
		virtual void InputKey(float dt, CAMERA_MOVEMENT direction);
		virtual void InputMouse(float deltaX, float deltaY);
		virtual void InputScroll(float deltaX, float deltaY);
	};
}


