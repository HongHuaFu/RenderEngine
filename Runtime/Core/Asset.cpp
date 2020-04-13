#include "Asset.hpp"
#include "../Core/Macro.hpp"

#include "../Render/Texture.hpp"
#include "../Render/Shader.hpp"
#include "../Render/TextureCube.hpp"

#include "../IO/LoadShader.hpp"
#include "../IO/LoadTexture.hpp"

#include "../Scene/Scene.hpp"
#include "../Scene/SceneNode.hpp"


namespace RE
{
	std::map<unsigned int, Shader> Asset::m_Shaders = std::map<unsigned int, Shader>();
	std::map<unsigned int, Texture> Asset::m_Textures = std::map<unsigned int, Texture>();
	std::map<unsigned int, TextureCube> Asset::m_TexturesCube = std::map<unsigned int, TextureCube>();

	void Asset::Init()
	{
		// 显示调用Asset::Init()来初始化
		// 加载通用资源
		LoadShader("Hdr2CubeMap","Asset/Shader/Hdr2CubeMap.vs","Asset/Shader/Hdr2CubeMap.fs");
		LoadShader("SkyBox","Asset/Shader/SkyBox.vs","Asset/Shader/SkyBox.fs");
		
	}

	void Asset::Clean()
	{
		// Shader无需释放
		// 贴图无需释放 ？
		// TODO: 使用更好的释放资源方式
	}

	Shader* Asset::LoadShader(std::string name,std::string vsPath,std::string fsPath,std::vector<std::string> defines)
	{
		unsigned int id = SID(name);

		// 遍历容器里的着色器 若已存在则直接返回该着色器地址 否则创建新的着色器
		if(Asset::m_Shaders.find(id) != Asset::m_Shaders.end())
			return &Asset::m_Shaders[id];

		Shader shader = LoadShader::Load(name, vsPath, fsPath, defines);
		Asset::m_Shaders[id] = shader;
		return &Asset::m_Shaders[id];
	}

	Shader* Asset::GetShader(std::string name)
	{
		unsigned int id = SID(name);

		if (Asset::m_Shaders.find(id) != Asset::m_Shaders.end())
		{
			return &Asset::m_Shaders[id];
		}
		else
		{
			LOG_WARN("Requested shader: {0} not found!", name);
			return nullptr;
		}
	}

	Texture* Asset::LoadTexture(std::string name,std::string path,unsigned int target,unsigned int format,bool srgb)
	{
		unsigned int id = SID(name);

		if (Asset::m_Textures.find(id) != Asset::m_Textures.end())
			return &Asset::m_Textures[id];

		LOG_TRACE("Loading texture file at: {0}.",path);

		Texture texture = LoadTexture::Load(path, target, format, srgb);

		LOG_TRACE("Succesfully loaded: {0}.",path);

		if (texture.m_Width > 0)
		{
			Asset::m_Textures[id] = texture;
			return &Asset::m_Textures[id];
		}
		else
		{
			LOG_WARN("UnUseful texture format,its width is {0}",texture.m_Width);
			return nullptr;
		}
	}

	Texture* Asset::GetTexture(std::string name)
	{
		unsigned int id = SID(name);

		if (Asset::m_Textures.find(id) != Asset::m_Textures.end())
		{
			return &Asset::m_Textures[id];
		}
		else
		{
			LOG_WARN("Requested texture: {0} not found!",name);
			return nullptr;
		}
	}

	Texture* Asset::LoadHDR(std::string name,std::string path)
	{
		unsigned int id = SID(name);

		if (Asset::m_Textures.find(id) != Asset::m_Textures.end())
			return &Asset::m_Textures[id];

		Texture texture = LoadTexture::LoadHDRTexture(path);
		
		if (texture.m_Width > 0)
		{
			Asset::m_Textures[id] = texture;
			return &Asset::m_Textures[id];
		}
		else
		{
			return nullptr;
		}
	}


	TextureCube* Asset::LoadTextureCube(std::string name, std::string folder)
	{
		unsigned int id = SID(name);

		if (Asset::m_TexturesCube.find(id) != Asset::m_TexturesCube.end())
			return &Asset::m_TexturesCube[id];

		TextureCube texture = LoadTexture::LoadTextureCube(folder);
		Asset::m_TexturesCube[id] = texture;
		return &Asset::m_TexturesCube[id];
	}


	TextureCube* Asset::GetTextureCube(std::string name)
	{
		unsigned int id = SID(name);

		if (Asset::m_TexturesCube.find(id) != Asset::m_TexturesCube.end())
		{
			return &Asset::m_TexturesCube[id];
		}
		else
		{
			LOG_WARN("Requested texture cube: {0} not found!",name);
			return nullptr;
		}
	}

	
}

