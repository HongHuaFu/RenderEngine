#include "Loader.hpp"
#include "../Core/Macro.hpp"
#include "../Shading/Texture.hpp"
#include "LoadShader.hpp"
#include "../Shading/Shader.hpp"
#include "../Shading/Texture.hpp"
#include "LoadTexture.hpp"

namespace Engine
{
	std::map<unsigned int, Shader>  Loader::m_Shaders      = std::map<unsigned int, Shader>();
	std::map<unsigned int, Texture> Loader::m_Textures     = std::map<unsigned int, Texture>();

	void Loader::Init()
	{
		Texture placeholderTexture;
	}

	void Loader::Clean()
	{
	
	}

	Shader* Loader::LoadShader(std::string name,
							   std::string vsPath,
							   std::string fsPath,
							   std::vector<std::string> defines)
	{
		unsigned int id = SID(name);

		if(Loader::m_Shaders.find(id) != Loader::m_Shaders.end())
			return &Loader::m_Shaders[id];

		Shader shader = LoadShader::Load(name, vsPath, fsPath, defines);
		Loader::m_Shaders[id] = shader;
		return &Loader::m_Shaders[id];
	}

	Shader* Loader::GetShader(std::string name)
	{
		unsigned int id = SID(name);

		if (Loader::m_Shaders.find(id) != Loader::m_Shaders.end())
		{
			return &Loader::m_Shaders[id];
		}
		else
		{
			LOG_WARN("Requested shader: {0} not found!", name);
			return nullptr;
		}
	}

	Texture* Loader::LoadTexture(std::string name,
							     std::string path,
								 unsigned int target,
								 unsigned int format,
								 bool srgb)
	{
		unsigned int id = SID(name);

		if (Loader::m_Textures.find(id) != Loader::m_Textures.end())
			return &Loader::m_Textures[id];

		LOG_TRACE("Loading texture file at: {0}.",path);

		Texture texture = LoadTexture::Load(path, target, format, srgb);

		LOG_TRACE("Succesfully loaded: {0}.",path);

		if (texture.m_Width > 0)
		{
			Loader::m_Textures[id] = texture;
			return &Loader::m_Textures[id];
		}
		else
		{
			LOG_WARN("UnUseful texture format,its width is {0}",texture.m_Width);
			return nullptr;
		}
	}

	Texture* Loader::GetTexture(std::string name)
	{
		unsigned int id = SID(name);

		if (Loader::m_Textures.find(id) != Loader::m_Textures.end())
		{
			return &Loader::m_Textures[id];
		}
		else
		{
			LOG_WARN("Requested texture: {0} not found!",name);
			return nullptr;
		}
	}

}

