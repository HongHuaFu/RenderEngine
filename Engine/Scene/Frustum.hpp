#ifndef ENGINE_FRUSTUM_HPP
#define ENGINE_FRUSTUM_HPP

#include <glm/glm.hpp>


namespace Engine
{
	class Camera;

	// �㷨ʽ
	struct FrustumPlane
	{
		glm::vec3 Normal;
		float      D;

		void SetNormalD(glm::vec3 normal, glm::vec3 point)
		{
			Normal = glm::normalize(normal);
			D      = -glm::dot(Normal, point);
		}

		float Distance(glm::vec3 point)
		{
			return glm::dot(Normal, point) + D;
		}
	};

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

		bool Intersect(glm::vec3 point);
		bool Intersect(glm::vec3 point, float radius);
		bool Intersect(glm::vec3 boxMin, glm::vec3 boxMax);
	};
}


#endif // !ENGINE_FRUSTUM_HPP
