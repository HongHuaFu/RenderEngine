#pragma once

#include <map>
#include <vector>

#include <glad/glad.h>

namespace RE
{
	class Shader;
	class Texture;
	class SceneNode;
	class TextureCube;

	// 静态类
	class Asset
	{
	private:
		Asset() = delete;
	private:
		static std::map<unsigned int, Shader> m_Shaders;
		static std::map<unsigned int, Texture> m_Textures;
		static std::map<unsigned int, TextureCube> m_TexturesCube;

		
	public:
		static void Init();
		static void Clean();

		// Getter函数返回指针避免临时变量拷贝构造
		static Shader* LoadShader(std::string, std::string, std::string, std::vector<std::string> defines = std::vector<std::string>());
		static Shader* GetShader(std::string);

		static Texture* LoadTexture(std::string, std::string, unsigned int target = GL_TEXTURE_2D, unsigned int format = GL_RGBA, bool srgb = false);
		static Texture* LoadHDR(std::string, std::string);
		static Texture* GetTexture(std::string name);
		
		static TextureCube* LoadTextureCube(std::string,std::string);
		static TextureCube* GetTextureCube(std::string);

	};
}