#ifndef ENGINE_LOAD_TEXTURE_HPP
#define ENGINE_LOAD_TEXTURE_HPP

#include <string>


namespace Engine
{
	class Texture;

	class LoadTexture
	{
	public:
		static Texture Load(std::string path,
							unsigned int target,
							unsigned int internalFormat,
							bool srgb = false);
	};
	
	
}


#endif 
