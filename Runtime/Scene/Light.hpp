#pragma once

#include <glm/glm.hpp>

namespace RE
{
	class RenderTarget;

	class DirectionalLight
	{
	public:
		glm::vec3 Direction = glm::vec3(0.0f);
		glm::vec3 Color = glm::vec3(1.0f);
		float Intensity = 1.0f;

		bool CastShadows = true;
		RenderTarget* ShadowMapRT;
		glm::mat4 LightSpaceViewProjection;
	};

	class PointLight
	{
	public:
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Color = glm::vec3(1.0f);
		float Intensity = 1.0f;
		float Radius = 1.0f;
		bool Visible = true;
		bool RenderMesh = false;
	};
}