#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace RE
{
	enum class Camera_Movement 
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	const float YAW = -90.0f;
	const float PITCH =  0.0f;
	const float SPEED =  2.5f;
	const float SENSITIVITY =  0.1f;
	const float ZOOM =  45.0f;

	class FlyCamera
	{
	public:
		// 相机属性
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		// 欧拉角
		float Yaw;
		float Pitch;

		// 相机选项
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;
		float Aspect;

		FlyCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
		{
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;
			UpdateCameraVectors();
		}
	
		FlyCamera(float posX,float posY,float posZ,float upX,float upY,float upZ,float yaw, float pitch)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
		{
			Position = glm::vec3(posX, posY, posZ);
			WorldUp = glm::vec3(upX, upY, upZ);
			Yaw = yaw;
			Pitch = pitch;
			UpdateCameraVectors();
		}

		// 返回相机View矩阵
		inline glm::mat4 GetViewMatrix()
		{
			return glm::lookAt(Position, Position + Front, Up);
		}

		inline glm::mat4 GetProjectMatrix(float zNear = 0.1f,float zFar = 100.0f)
		{
			return glm::perspective(glm::radians(Zoom), Aspect, zNear, zFar);
		}

		inline glm::mat4 GetProjectMatrix(float left,float right,float up,float down)
		{
			return glm::ortho(left,right,up,down);
		}

		void ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);

	private:
		void UpdateCameraVectors();
	};
}


