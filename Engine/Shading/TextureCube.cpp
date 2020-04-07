#include "TextureCube.hpp"

namespace Engine
{
	TextureCube:: TextureCube() { }
	TextureCube::~TextureCube() { }

	void TextureCube::DefaultInitialize(unsigned int width, 
										unsigned int height, 
										unsigned int format, 
										unsigned int type, 
										bool mipmap)
	{
		glGenTextures(1, &m_ID);

		m_FaceWidth = width;
		m_FaceHeight = height;
		m_Format = format;
		m_Type = type;
		m_Mipmapping = mipmap;

		if (type == GL_HALF_FLOAT && format == GL_RGB)
			m_InternalFormat = GL_RGB16F;
		else if (type == GL_FLOAT && format == GL_RGB)
			m_InternalFormat = GL_RGB32F;
		else if (type == GL_HALF_FLOAT && format == GL_RGBA)
			m_InternalFormat = GL_RGBA16F;
		else if (type == GL_FLOAT && format == GL_RGBA)
			m_InternalFormat = GL_RGBA32F;

		Bind();
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, m_FilterMin);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, m_FilterMax);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, m_WrapS);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, m_WrapT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, m_WrapR);

		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_InternalFormat, width, height, 0, format, type, 0);
		}
		if (mipmap)
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	void TextureCube::GenerateFace(unsigned int face, 
								   unsigned int width, 
								   unsigned int height, 
								   unsigned int format, 
								   unsigned int type, 
								   unsigned char* data)
	{
		if(m_FaceWidth == 0)
			glGenTextures(1, &m_ID);

		m_FaceWidth = width;
		m_FaceHeight = height;
		m_Format = format;
		m_Type = type;

		Bind();

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, m_FilterMin);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, m_FilterMax);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, m_WrapS);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, m_WrapT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, m_WrapR);

		glTexImage2D(face, 0, format, width, height, 0, format, type, data);
	}


	void TextureCube::SetMipFace(unsigned int face, 
								 unsigned int width, 
								 unsigned int height, 
								 unsigned int format, 
								 unsigned int type, 
								 unsigned int mipLevel, 
								 unsigned char *data)
	{
		Bind();
		glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, mipLevel, 0, 0, width, height, format, type, data);
	}


	void TextureCube::Resize(unsigned int width, unsigned int height)
	{
		m_FaceWidth = width;
		m_FaceHeight = height;

		Bind();
		for (unsigned int i = 0; i < 6; ++i)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, m_Format, width, height, 0, m_Format, m_Type, 0);
	}


	void TextureCube::Bind(int unit)
	{
		if (unit >= 0)
			glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
	}


	void TextureCube::UnBind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}

