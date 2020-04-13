#include "Texture.hpp"
#include "../Core/Macro.hpp"

namespace RE
{
	// 1DÌùÍ¼
	void Texture::Create(unsigned int width,unsigned int internalFormat,unsigned int format,unsigned int type,void* data)
	{
		glGenTextures(1, &m_ID);

		m_Width = width;
		m_Height = 0;
		m_Depth = 0;
		m_InternalFormat = internalFormat;
		m_Format = format;
		m_Type = type;

		LOG_ASSERT(m_Target == GL_TEXTURE_1D,"Texture format error.");
		Bind();
		glTexImage1D(m_Target, 0, internalFormat, width, 0, format, type, data);
		glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, m_FilterMin);
		glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, m_FilterMax);
		glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, m_WrapS);
		if(m_Mipmapping)
			glGenerateMipmap(m_Target);
		UnBind();
	}

	// 2DÌùÍ¼
	void Texture::Create(unsigned int width,unsigned int height,unsigned int internalFormat,unsigned int format,unsigned int type,void* data)
	{
		glGenTextures(1, &m_ID);

		m_Width = width;
		m_Height = height;
		m_Depth = 0;
		m_InternalFormat = internalFormat;
		m_Format = format;
		m_Type = type;

		LOG_ASSERT(m_Target == GL_TEXTURE_2D,"Texture format error.");

		Bind();
		glTexImage2D(m_Target, 0, internalFormat, width, height, 0, format, type, data);
		glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, m_FilterMin);
		glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, m_FilterMax);
		glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, m_WrapS);
		glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, m_WrapT);
		if (m_Mipmapping)
			glGenerateMipmap(m_Target);
		UnBind();
	}

	// 3DÌùÍ¼
	void Texture::Create(unsigned int width,unsigned int height,unsigned int depth,unsigned int internalFormat,unsigned int format,unsigned int type,void * data)
	{
		glGenTextures(1, &m_ID);

		m_Width = width;
		m_Height = height;
		m_Depth = depth;
		m_InternalFormat = internalFormat;
		m_Format = format;
		m_Type = type;

		LOG_ASSERT(m_Target == GL_TEXTURE_3D,"Texture format error.");

		Bind();
		glTexImage3D(m_Target, 0, internalFormat, width, height, depth, 0, format, type, data);
		glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, m_FilterMin);
		glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, m_FilterMax);
		glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, m_WrapS);
		glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, m_WrapT);
		glTexParameteri(m_Target, GL_TEXTURE_WRAP_R, m_WrapR);
		if (m_Mipmapping)
			glGenerateMipmap(m_Target);
		UnBind();
	}


	void Texture::ReSize(unsigned int width,unsigned int height,unsigned int depth)
	{
		Bind();
		if (m_Target == GL_TEXTURE_1D)
		{
			glTexImage1D(GL_TEXTURE_1D, 0, m_InternalFormat, width, 0, m_Format, m_Type, 0);
		}
		else if (m_Target == GL_TEXTURE_2D)
		{

			LOG_ASSERT(height > 0,"Texture height <= 0.");
			glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_Format, m_Type, 0);
		}
		else if (m_Target == GL_TEXTURE_3D)
		{
			LOG_ASSERT(height > 0 && depth > 0 ,"Texture height or depth <= 0.");
			glTexImage3D(GL_TEXTURE_3D, 0, m_InternalFormat, width, height, depth, 0, m_Format, m_Type, 0);
		}
	}

	void Texture::Bind(int unit)
	{
		if(unit >= 0)
			glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(m_Target, m_ID); 
	}

	void Texture::UnBind()
	{
		glBindTexture(m_Target, 0); 
	}

	void Texture::SetWrapMode(unsigned int wrapMode,bool bind)
	{
		if(bind)
			Bind();
		if (m_Target == GL_TEXTURE_1D)
		{
			m_WrapS = wrapMode;
			glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, wrapMode);
		}
		else if (m_Target == GL_TEXTURE_2D)
		{
			m_WrapS = wrapMode;
			m_WrapT = wrapMode;
			glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, wrapMode);
			glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, wrapMode);
		}
		else if (m_Target == GL_TEXTURE_3D)
		{
			m_WrapS = wrapMode;
			m_WrapT = wrapMode;
			m_WrapR = wrapMode;
			glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, wrapMode);
			glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, wrapMode);
			glTexParameteri(m_Target, GL_TEXTURE_WRAP_R, wrapMode);
		}
	}

	void Texture::SetFilterMin(unsigned int filter,bool bind)
	{
		if(bind)
			Bind();
		glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, filter);
	}

	void Texture::SetFilterMax(unsigned int filter,bool bind)
	{
		if (bind)
			Bind();
		glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, filter);
	}




}


