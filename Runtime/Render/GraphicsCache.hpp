#pragma once

#include <glad/glad.h>

namespace RE
{
	// 渲染状态设置
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

		// 当前激活的Shader
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
