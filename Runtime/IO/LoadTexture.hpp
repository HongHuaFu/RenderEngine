#pragma once

#include <string>

namespace RE
{
	class Texture;
	class TextureCube;

	class LoadTexture
	{
	public:
		static Texture Load(std::string,unsigned int,unsigned int,bool srgb = false);
		static Texture LoadHDRTexture(std::string);
		static TextureCube LoadTextureCube(std::string, std::string, std::string, std::string, std::string, std::string);
		static TextureCube LoadTextureCube(std::string);
	};
}

