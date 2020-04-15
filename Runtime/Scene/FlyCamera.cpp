#include "FlyCamera.hpp"
#include <glm/gtx/compatibility.hpp>

namespace RE
{
	FlyCamera::FlyCamera(glm::vec3 position, glm::vec3 forward, glm::vec3 up) 
	: Camera(position, forward, up)
	{
		m_TargetYaw = Yaw = 0.0f;
		m_TargetPitch = Pitch = 0.0f;
		Forward = forward;
		m_WorldUp = Up;
		m_TargetPosition = position;
	}

	void FlyCamera::Update(float dt)
	{
		Frustum.Update(this);
		Camera::Update(dt);
		// 相机移动插值
		Position = glm::lerp(Position, m_TargetPosition, glm::clamp(dt * Damping,0.0f,1.0f));
		Yaw = glm::lerp(Yaw, m_TargetYaw, glm::clamp(dt * Damping * 2.0f,0.0f,1.0f));
		Pitch = glm::lerp(Pitch, m_TargetPitch, glm::clamp(dt * Damping * 2.0f,0.0f,1.0f));

		// 计算正交坐标系
		// 施密特正交化
		glm::vec3 newForward;
		newForward.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
		newForward.y = sin(glm::radians(Pitch));
		newForward.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
		Forward = glm::normalize(newForward);
		Right = glm::normalize(glm::cross(Forward, m_WorldUp));
		Up = glm::cross(Right, Forward);

		// 更新View矩阵
		UpdateView();
	}

	// 无插值更新
	void FlyCamera::Update()
	{
		Frustum.Update(this);
		Camera::Update();

		Position = m_TargetPosition; 
		Yaw = m_TargetYaw;
		Pitch = m_TargetPitch;

		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Forward = glm::normalize(front);
		Right = glm::normalize(glm::cross(Forward, m_WorldUp));  
		Up = glm::normalize(glm::cross(Right, Forward));


		// 更新View矩阵
		UpdateView();
	}

	void FlyCamera::InputKey(float dt, CAMERA_MOVEMENT direction)
	{
		float speed = MovementSpeed * dt;
		if (direction      == CAMERA_MOVEMENT::FORWARD)
			m_TargetPosition = m_TargetPosition + Forward*speed;
		else if (direction == CAMERA_MOVEMENT::BACK)
			m_TargetPosition = m_TargetPosition - Forward*speed;
		else if (direction == CAMERA_MOVEMENT::LEFT)
			m_TargetPosition = m_TargetPosition - Right*speed;
		else if (direction == CAMERA_MOVEMENT::RIGHT)
			m_TargetPosition = m_TargetPosition + Right*speed;
		else if (direction == CAMERA_MOVEMENT::UP)
			m_TargetPosition = m_TargetPosition + m_WorldUp*speed;
		else if (direction == CAMERA_MOVEMENT::DOWN)
			m_TargetPosition = m_TargetPosition - m_WorldUp*speed;
	}

	void FlyCamera::InputMouse(float deltaX, float deltaY)
	{
		float xmovement = deltaX * MouseSensitivty;
		float ymovement = deltaY * MouseSensitivty;

		m_TargetYaw += xmovement;
		m_TargetPitch += ymovement;

		// 俯仰角限制
		if (m_TargetPitch > 89.0f)  m_TargetPitch =  89.0f;
		if (m_TargetPitch < -89.0f) m_TargetPitch = -89.0f;

	}

	void FlyCamera::InputScroll(float deltaX, float deltaY)
	{
		MovementSpeed = glm::clamp(MovementSpeed + deltaY * 1.0f, 1.0f, 25.0f); 
		Damping = glm::clamp(Damping + deltaX * 0.5f, 1.0f, 25.0f);
	}
}