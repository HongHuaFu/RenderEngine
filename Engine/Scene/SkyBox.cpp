#include "SkyBox.hpp"
#include "Scene.hpp"
#include "../IO/Loader.hpp"
#include "../Shading/Material.hpp"
#include "../Geometry/Cube.hpp"
#include "../Renderer/Renderer.hpp"



namespace Engine
{
	SkyBox::SkyBox() : SceneNode(Scene::CounterID++)
	{
		Scene::Root->AddChild(this);

		m_Shader  = Loader::LoadShader("background", "shaders/background.vs", "shaders/background.fs");
		Material  = new Engine::Material(m_Shader);
		Mesh      = new Cube();
		BoxMin    = glm::vec3(-99999.0);
		BoxMax    = glm::vec3( 99999.0);

		Material->SetFloat("Exposure", 1.0f);
		Material->DepthCompare = GL_LEQUAL;
		Material->Cull = false;
		Material->ShadowCast = false;
		Material->ShadowReceive = false;
	}

	SkyBox::~SkyBox()
	{

	}
	// --------------------------------------------------------------------------------------------
	void SkyBox::SetCubemap(TextureCube* cubemap)
	{
		m_CubeMap = cubemap;
		Material->SetTextureCube("background", m_CubeMap, 0);
	}
}

