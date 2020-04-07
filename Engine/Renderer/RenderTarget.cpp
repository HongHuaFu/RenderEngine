#include "RenderTarget.hpp"
#include "../Core/Macro.hpp"

namespace Engine
{
	RenderTarget::RenderTarget(unsigned int width,
							   unsigned int height,
							   unsigned int type,
							   unsigned int nrColorAttachments,
							   bool depthAndStencil)
	{
		Width  = width;
		Height = height;
		Type   = type;

		glGenFramebuffers(1, &ID);
		glBindFramebuffer(GL_FRAMEBUFFER, ID);

		for (unsigned int i = 0; i < nrColorAttachments; ++i)
		{
			Texture texture;
			texture.m_FilterMin = GL_LINEAR;
			texture.m_FilterMax = GL_LINEAR;
			texture.m_WrapS = GL_CLAMP_TO_EDGE;
			texture.m_WrapT = GL_CLAMP_TO_EDGE;
			texture.m_Mipmapping = false;

			GLenum internalFormat = GL_RGBA;
			if(type == GL_HALF_FLOAT)
				internalFormat = GL_RGBA16F;
			else if (type == GL_FLOAT)
				internalFormat = GL_RGBA32F;
			texture.Create(width, height, internalFormat, GL_RGBA, type, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture.m_ID, 0);
			m_ColorAttachments.push_back(texture);
		}
		
		HasDepthAndStencil = depthAndStencil;
		if (depthAndStencil)
		{
			Texture texture;
			texture.m_FilterMin = GL_LINEAR;
			texture.m_FilterMax = GL_LINEAR;
			texture.m_WrapS = GL_CLAMP_TO_EDGE;
			texture.m_WrapT = GL_CLAMP_TO_EDGE;
			texture.m_Mipmapping = false;
			texture.Create(width, height, GL_DEPTH_STENCIL, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture.m_ID, 0);
			m_DepthStencil = texture;
		}
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_ERROR("Framebuffer not complete!");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	Texture* RenderTarget::GetDepthStencilTexture()
	{
		return &m_DepthStencil;
	}


	Texture* RenderTarget::GetColorTexture(unsigned int index)
	{
		if(index < m_ColorAttachments.size())
			return &m_ColorAttachments[index];
		else
		{
			LOG_WARN("RenderTarget color texture requested, but index not available: {0}.",std::to_string(index));
			return nullptr;
		}
	}

	void RenderTarget::ReSize(unsigned int width, unsigned int height)
	{
		Width = width;
		Height = height;

		for (unsigned int i = 0; i < m_ColorAttachments.size(); ++i)
		{
			m_ColorAttachments[i].ReSize(width, height);
		}

		if (HasDepthAndStencil)
		{
			m_DepthStencil.ReSize(width, height);
		}
	}

	void RenderTarget::SetTarget(GLenum target)
	{
		m_Target = target;
	}
}
