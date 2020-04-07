#ifndef ENGINE_GRAPHIC_CACHE_HPP
#define ENGINE_GRAPHIC_CACHE_HPP

#include <glad/glad.h>

namespace Engine
{
	class GraphicCache
	{
	private:
		bool m_DepthTest;
		bool m_Blend;
		bool m_CullFace;

		GLenum m_DepthFunc;
		GLenum m_BlendSrc;
		GLenum m_BlendDst;
		GLenum m_FrontFace;
		GLenum m_PolygonMode;

		unsigned int m_ActiveShaderID;
	public:
		GraphicCache();
		~GraphicCache();

		void SetDepthTest(bool enable);
		void SetDepthFunc(GLenum depthFunc);
		void SetBlend(bool enable);
		void SetBlendFunc(GLenum src, GLenum dst);
		void SetCull(bool enable);
		void SetCullFace(GLenum face);
		void SetPolygonMode(GLenum mode);

		void SwitchShader(unsigned int ID);
	};
}

#endif // !ENGINE_GRAPHIC_CACHE_HPP
