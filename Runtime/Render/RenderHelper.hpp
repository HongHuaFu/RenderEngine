#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "../Render/CommandBuffer.hpp"

namespace RE
{
	class SceneNode;
	class TextureCube;
	class Renderer;
	class Texture;
	class RenderTarget;
	class Material;
	class Quad;

	class RenderHelper
	{
	private:
		Renderer* m_Renderer;
		Quad* m_Quad;
		// CubeMap渲染时使用到的FBO和RBO
		unsigned int m_FramebufferCubemap; 
		unsigned int m_CubemapDepthRBO;

	public:
		RenderHelper(Renderer* r);
		~RenderHelper();

	public:
		void RenderToCubeMap(SceneNode* scene, TextureCube* target, glm::vec3 position = glm::vec3(0.0f), unsigned int mipLevel = 0);

		void RenderToCubemap(std::vector<RenderCommand>& renderCommands, TextureCube* target, glm::vec3 position = glm::vec3(0.0f), unsigned int mipLevel = 0);

		// 一次全屏的后处理Blit
		void Blit(Texture* src, Material* material, RenderTarget* dst = nullptr, std::string textureUniformName = "TexSrc");
	};
}