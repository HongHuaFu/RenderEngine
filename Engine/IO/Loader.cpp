#include "Loader.hpp"
#include "../Core/Macro.hpp"
#include "../Shading/Texture.hpp"
#include "LoadShader.hpp"
#include "../Shading/Shader.hpp"
#include "../Shading/TextureCube.hpp"
#include "LoadTexture.hpp"
#include "../Scene/Scene.hpp"
#include "../Scene/SceneNode.hpp"
#include "../Renderer/Renderer.hpp"
#include "LoadMesh.hpp"

namespace Engine
{
	std::map<unsigned int, Shader>  Loader::m_Shaders      = std::map<unsigned int, Shader>();
	std::map<unsigned int, Texture> Loader::m_Textures     = std::map<unsigned int, Texture>();
	std::map<unsigned int, TextureCube> Loader::m_TexturesCube = std::map<unsigned int, TextureCube>();
	std::map<unsigned int, SceneNode*>  Loader::m_Meshes   = std::map<unsigned int, SceneNode*>();
	// 

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

	Texture* Loader::LoadHDR(std::string name,std::string path)
	{
		unsigned int id = SID(name);

		// if texture already exists, return that handle
		if (Loader::m_Textures.find(id) != Loader::m_Textures.end())
			return &Loader::m_Textures[id];

		Texture texture = LoadTexture::LoadHDRTexture(path);
		// make sure texture got properly loaded
		if (texture.m_Width > 0)
		{
			Loader::m_Textures[id] = texture;
			return &Loader::m_Textures[id];
		}
		else
		{
			return nullptr;
		}
	}


	SceneNode* Loader::LoadMesh(Renderer* renderer, std::string name, std::string path)
	{
		unsigned int id = SID(name);

		// if mesh's scene node was already loaded before, copy the scene node's memory and return 
		// the copied reference. We return a copy as the moment the global scene deletes the 
		// returned node, all other and next requested scene nodes of this model will end up as
		// dangling pointers.
		if (Loader::m_Meshes.find(id) != Loader::m_Meshes.end())
		{
			return Scene::MakeSceneNode(Loader::m_Meshes[id]);
		}

		// MeshLoader::LoadMesh initializes a scene node hierarchy on the heap. We are responsible 
		// for managing the memory; keep a reference to the root node of the model scene. 
		SceneNode* node = LoadMesh::Load(renderer, path);
		Loader::m_Meshes[id] = node;

		// return a copied reference through the scene to prevent dangling pointers. 
		// See description above.
		return Scene::MakeSceneNode(node);
	}
	// --------------------------------------------------------------------------------------------
	SceneNode* Loader::GetMesh(std::string name)
	{
		unsigned int id = SID(name);

		// if mesh's scene node was already loaded before, copy the scene node's memory and return 
		// the copied reference. We return a copy as the moment the global scene deletes the 
		// returned node, all other and next requested scene nodes of this model will end up as
		// dangling pointers.
		if (Loader::m_Meshes.find(id) != Loader::m_Meshes.end())
		{
			return Scene::MakeSceneNode(Loader::m_Meshes[id]);
		}
		else
		{
			LOG_WARN("Requested mesh: {0} not found!",name);
			return nullptr;
		}
	}

	TextureCube* Loader::LoadTextureCube(std::string name, std::string folder)
	{
		unsigned int id = SID(name);

		// if texture already exists, return that handle
		if (Loader::m_TexturesCube.find(id) != Loader::m_TexturesCube.end())
			return &Loader::m_TexturesCube[id];

		TextureCube texture = LoadTexture::LoadTextureCube(folder);
		Loader::m_TexturesCube[id] = texture;
		return &Loader::m_TexturesCube[id];
	}
	// --------------------------------------------------------------------------------------------
	TextureCube* Loader::GetTextureCube(std::string name)
	{
		unsigned int id = SID(name);

		// if shader exists, return that handle
		if (Loader::m_TexturesCube.find(id) != Loader::m_TexturesCube.end())
		{
			return &Loader::m_TexturesCube[id];
		}
		else
		{
			LOG_WARN("Requested texture cube: {0} not found!",name);
			return nullptr;
		}
	}
}

