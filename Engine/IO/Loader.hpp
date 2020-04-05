#ifndef ENGINE_LOADER_HPP
#define ENGINE_LOADER_HPP

#include <map>
#include <vector>

// TODO: ÕÍ…∆Loader
namespace Engine
{
	class Shader;
	class Texture;

	class Loader
	{
	private:
		Loader();
	private:
		static std::map<unsigned int, Shader>      m_Shaders;
		static std::map<unsigned int, Texture>     m_Textures;
		

	public:
		static void Init();
		static void Clean();

		static Shader* LoadShader(std::string name, 
								  std::string vsPath, 
								  std::string fsPath, 
								  std::vector<std::string> defines = std::vector<std::string>());

		static Shader* GetShader(std::string name);

		static Texture* LoadTexture(std::string name, 
								    std::string path, 
									unsigned int target = 0x0DE1, // GL_TEXTURE_2D
									unsigned int format = 0x1908, // GL_RGBA
									bool srgb = false);

		static Texture* GetTexture(std::string name);
	};
}

#endif