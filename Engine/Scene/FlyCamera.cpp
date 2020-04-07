#include "FlyCamera.hpp"
#include <glm/ext.hpp>
#include "../Math/Math.hpp"


namespace Engine
{
	FlyCamera::FlyCamera(glm::vec3 position, glm::vec3 forward, glm::vec3 up)
	: Camera(position, forward, up)
	{
		Yaw = -90.0f;

		Forward = forward;
		m_WorldUp = Up;
		m_TargetPosition = position;
	}

	void FlyCamera::Update(float dt)
	{
		Camera::Update(dt);
		
		Position = Math::lerp(Position, m_TargetPosition, glm::clamp(dt * Damping,0.0f,1.0f));
		Yaw      = Math::lerp(Yaw, m_TargetYaw, glm::clamp(dt * Damping * 2.0f,0.0f,1.0f));
		Pitch    = Math::lerp(Pitch, m_TargetPitch, glm::clamp(dt * Damping * 2.0f,0.0f,1.0f));


		glm::vec3 newForward;
		newForward.x = cos(0.0174533 * Pitch) * cos(0.0174533 * Yaw);
		newForward.y = sin(0.0174533 * Pitch);
		newForward.z = cos(0.0174533 * Pitch) * sin(0.0174533 * Yaw);
		Forward = glm::normalize(newForward);
		Right = glm::normalize(glm::cross(Forward, m_WorldUp));
		Up = glm::cross(Right, Forward);


		UpdateView();
	}
	

	void FlyCamera::InputKey(float dt, CAMERA_MOVEMENT direction)
	{
		float speed = MovementSpeed * dt;
		if (direction      == CAMERA_FORWARD)
			m_TargetPosition = m_TargetPosition + Forward*speed;
		else if (direction == CAMERA_BACK)
			m_TargetPosition = m_TargetPosition - Forward*speed;
		else if (direction == CAMERA_LEFT)
			m_TargetPosition = m_TargetPosition - Right*speed;
		else if (direction == CAMERA_RIGHT)
			m_TargetPosition = m_TargetPosition + Right*speed;
		else if (direction == CAMERA_UP)
			m_TargetPosition = m_TargetPosition + m_WorldUp*speed;
		else if (direction == CAMERA_DOWN)
			m_TargetPosition = m_TargetPosition - m_WorldUp*speed;
	}


	void FlyCamera::InputMouse(float deltaX, float deltaY)
	{
		float xmovement = deltaX * MouseSensitivty;
		float ymovement = deltaY * MouseSensitivty;

		m_TargetYaw   += xmovement;
		m_TargetPitch += ymovement;

		
		if(m_TargetYaw == 0.0f) m_TargetYaw = 0.01f;
		if(m_TargetPitch == 0.0f) m_TargetPitch = 0.01f;

	
		if (m_TargetPitch > 89.0f)  m_TargetPitch =  89.0f;
		if (m_TargetPitch < -89.0f) m_TargetPitch = -89.0f;
	}


	void FlyCamera::InputScroll(float deltaX, float deltaY)
	{
		MovementSpeed = glm::clamp(MovementSpeed + deltaY * 1.0f, 1.0f, 25.0f); 
		Damping       = glm::clamp(Damping       + deltaX * 0.5f, 1.0f, 25.0f);
	}
}

