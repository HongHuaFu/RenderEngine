#ifndef ENGINE_LOAD_TEXTURE_HPP
#define ENGINE_LOAD_TEXTURE_HPP

#include <string>


namespace Engine
{
	class Texture;
	class TextureCube;

	class LoadTexture
	{
	public:
		static Texture Load(std::string path,
							unsigned int target,
							unsigned int internalFormat,
							bool srgb = false);

		static Texture LoadHDRTexture(std::string path);
		// TODO(Joey): read and copy original cubemap order from GL specification
		static TextureCube LoadTextureCube(std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back);
		// assumes default names for cubemap faces
		static TextureCube LoadTextureCube(std::string folder);
	};
	
	
}


#endif 
