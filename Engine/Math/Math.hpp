#ifndef ENGINE_MATH_HPP
#define ENGINE_MATH_HPP

#include <glm/glm.hpp>

namespace Engine::Math
{
	const float PI  = 3.14159265359f;
	const float TAU = 6.28318530717f;

	inline float Deg2Rad(float degrees)
	{
		return degrees / 180.0f * PI;
	}
	inline double Deg2Rad(double degrees)
	{
		return degrees / 180.0 * PI;
	}

	inline float Rad2Deg(float radians)
	{
		return radians / PI * 180.0f;
	}
	inline double Rad2Deg(double radians)
	{
		return radians / PI * 180.0;
	}

	template <typename T>
	inline T lerp(const T& a, const T& b, const float t)
	{
		return (1.0f - t) * a + b * t;
	}

	inline glm::vec3 lerp(glm::vec3& a, glm::vec3& b, const float t)
	{
		glm::vec3 result;
		for (std::size_t i = 0; i < 3; ++i) {
			result[i] = lerp(a[i], b[i], t);
		}
		return result;
	}
}


#endif // !ENGINE_MATH_HPP
