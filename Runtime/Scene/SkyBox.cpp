#include "SkyBox.hpp"
#include "Scene.hpp"
#include "../Core/Asset.hpp"
#include "../Geometry/Cube.hpp"
#include "../Render/TextureCube.hpp"
#include "../Render/Material.hpp"


namespace RE
{
	SkyBox::SkyBox() : SceneNode(Scene::CounterID++,u8"��պ�")
	{
		Scene::Root->AddChild(this);

		auto shader = Asset::LoadShader("SkyBox::No LOD","Asset/Shader/SkyBox.vs","Asset/Shader/SkyBox.fs");
		Material = new RE::Material(shader);


		Mesh = new Cube();
		BoxMin = glm::vec3(-99999.0);
		BoxMax = glm::vec3(99999.0);

		Material->DepthCompare = GL_LEQUAL;

		// ��պн����޳�
		Material->Cull = false;

		// ��Ӱ����/���ɹر�
		Material->ShadowCast = false;
		Material->ShadowReceive = false;
	}

	SkyBox::~SkyBox()
	{

	}


	void SkyBox::SetCubemap(TextureCube* cubemap)
	{
		m_CubeMap = cubemap;
		Material->SetTextureCube("skybox", m_CubeMap, 0);
	}
}

