#include "LoadTexture.hpp"
#include "../Vendor/stb_image.h"
#include "../Core/Macro.hpp"
#include "../Shading/Texture.hpp"

namespace Engine
{
	Texture LoadTexture(std::string path,
						unsigned int target,
						unsigned int internalFormat,
						bool srgb)
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
}


