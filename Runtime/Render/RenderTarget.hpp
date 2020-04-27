#pragma once

#include <vector>
#include <glad/glad.h>

#include "../Render/Texture.hpp"

namespace RE
{
	// ֡����ĳ���
	class RenderTarget
	{
	private:
		unsigned int m_ID;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_Type;
		bool m_HasDepthAndStencil;

		// ��������
		unsigned int m_Target = GL_TEXTURE_2D;

		// ���/Stencil����
		Texture m_DepthStencil;

		// ��ǰ֡����Ķ����ɫ����洢����
		std::vector<Texture> m_ColorAttachments;

	public:
		inline void Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		}
		

		inline void UnBind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		inline unsigned int GetID()
		{
			return m_ID;
		}

	public:
		RenderTarget(unsigned int, unsigned int, unsigned int type = GL_UNSIGNED_BYTE, unsigned int nrColorAttachments = 1, bool depthAndStencil = true);

		Texture* GetDepthStencilTexture();
		Texture* GetColorTexture(unsigned int index);

		void ReSize(unsigned int width, unsigned int height);
		void SetTarget(unsigned int target);
	private:
		friend class RenderHelper;
		friend class PP_PBRIBLForward;
		friend class PP_Defferd_Lambert;
	};
}



