#include "LoadTexture.hpp"
#include "../Vendor/stb_image.h"
#include "../Core/Macro.hpp"
#include "../Render/Texture.hpp"
#include "../Render/TextureCube.hpp"

namespace RE
{
	Texture LoadTexture::Load(std::string path,unsigned int target,unsigned int internalFormat,bool srgb)
	{
		Texture texture;
		texture.m_Target = target;
		unsigned int inFormat = internalFormat;

		if(internalFormat == GL_RGB || internalFormat == GL_SRGB)
			inFormat = srgb ? GL_SRGB : GL_RGB;

		if(internalFormat == GL_RGBA || internalFormat == GL_SRGB_ALPHA)
			inFormat = srgb ? GL_SRGB_ALPHA : GL_RGBA;

		stbi_set_flip_vertically_on_load(true);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

		if (data)
		{
			unsigned int format;
			if(nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			if(target == GL_TEXTURE_1D)
				texture.Create(width, inFormat, format, GL_UNSIGNED_BYTE, data);
			else if (target == GL_TEXTURE_2D)
				texture.Create(width, height, inFormat, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			LOG_WARN("Texture failed to load at path: {0}." ,path);
			stbi_image_free(data);
			return texture;
		}

		return texture;
	}


	Texture LoadTexture::LoadHDRTexture(std::string path)
	{
		Texture texture;
		texture.m_Target = GL_TEXTURE_2D;
		texture.m_FilterMin = GL_LINEAR;
		texture.m_Mipmapping = false; 

		stbi_set_flip_vertically_on_load(true);

		if (stbi_is_hdr(path.c_str()))
		{
			int width, height, nrComponents;
			float *data = stbi_loadf(path.c_str(), &width, &height, &nrComponents, 0);
			if (data)
			{
				GLenum internalFormat, format;
				if (nrComponents == 3)
				{
					internalFormat = GL_RGB32F;
					format = GL_RGB;
				}
				else if (nrComponents == 4)
				{
					internalFormat = GL_RGBA32F;
					format = GL_RGBA;
				}

				texture.Create(width, height, internalFormat, format, GL_FLOAT, data);
				stbi_image_free(data);
			}
			texture.m_Width = width;
			texture.m_Height = height;

			LOG_TRACE("Load a HDR texture success: {0}.",path);
		}
		else
		{
			LOG_WARN("Trying to load a HDR texture with invalid path or texture is not HDR: {0}.",path);
		}

		return texture;
	}

	
	TextureCube LoadTexture::LoadTextureCube(std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back)
	{
		TextureCube texture;

		// Cubemap 禁止y反转
		stbi_set_flip_vertically_on_load(false);

		std::vector<std::string> faces = { top, bottom, left, right, front, back };
		for (unsigned int i = 0; i < faces.size(); ++i)
		{
			int width, height, nrComponents;
			unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);

			if (data)
			{
				GLenum format;
				if (nrComponents == 3)
					format = GL_RGB;
				else
					format = GL_RGBA;

				texture.GenerateFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, width, height, format, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				LOG_WARN("Cube texture at path: {0} failed to load.",faces[i]);
				stbi_image_free(data);
				return texture;
			}
		}
		if(texture.m_Mipmapping)
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		return texture;
	}
	

	// 使用默认的命名规则
	TextureCube LoadTexture::LoadTextureCube(std::string folder)
	{
		return LoadTexture::LoadTextureCube(folder + "right.jpg",
			folder + "left.jpg",
			folder + "top.jpg",
			folder + "bottom.jpg",
			folder + "front.jpg",
			folder + "back.jpg");
	}
}


