#ifndef ENGINE_RENDER_TARGET
#define ENGINE_RENDER_TARGET

#include <glad/glad.h>
#include <vector>
#include "../Shading/Texture.hpp"

namespace Engine
{
	class RenderTarget
	{
	private:
		friend class Renderer;
	public:
		unsigned int ID;

		unsigned int Width;
		unsigned int Height;
		unsigned int Type;

		bool HasDepthAndStencil;

	private:
		unsigned int m_Target = GL_TEXTURE_2D;
		Texture m_DepthStencil;
		std::vector<Texture> m_ColorAttachments;

	public:
		RenderTarget(unsigned int width, unsigned int height, 
					 unsigned int type = GL_UNSIGNED_BYTE, 
					 unsigned int nrColorAttachments = 1, 
					 bool depthAndStencil = true);

		Texture* GetDepthStencilTexture();
		Texture* GetColorTexture(unsigned int index);

		void ReSize(unsigned int width, unsigned int height);
		void SetTarget(GLenum target);
	};
}



#endif // !ENGINE_RENDER_TARGET
