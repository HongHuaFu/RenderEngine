#pragma once

#include <glm/glm.hpp>

namespace RE
{
	class Quad;
	class SceneNode;
	class TextureCube;
	class Renderer;
	class RenderHelper
	{
	private:
		Renderer* m_Renderer;

	public:
		RenderHelper(Renderer* r){ m_Renderer = r; }

	public:
		void RenderToCubeMap(SceneNode* scene, TextureCube* target, glm::vec3 position = glm::vec3(0.0f), unsigned int mipLevel = 0);
	};
}