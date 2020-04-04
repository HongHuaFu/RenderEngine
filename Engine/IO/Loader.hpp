#ifndef ENGINE_LOADER_HPP
#define ENGINE_LOADER_HPP

#include <map>

// TODO: ÕÍ…∆Loader
namespace Engine
{
	class Shader;
	class Texture;
	class TextureCube;
	class SceneNode;

	class Loader
	{
	private:
		static std::map<unsigned int, Shader>      m_Shaders;
		static std::map<unsigned int, Texture>     m_Textures;
		static std::map<unsigned int, TextureCube> m_TexturesCube;
		static std::map<unsigned int, SceneNode*>  m_Meshes;
	};
}

#endif