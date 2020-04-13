#include "SkyBox.hpp"
#include "Scene.hpp"
#include "../Core/Asset.hpp"
#include "../Geometry/Cube.hpp"
#include "../Render/TextureCube.hpp"
#include "../Render/Material.hpp"


namespace RE
{
	SkyBox::SkyBox() : SceneNode(Scene::CounterID++)
	{
		Scene::Root->AddChild(this);

		auto shader = Asset::GetShader("SkyBox");
		Material = new RE::Material(shader);

		auto hdr2cubemap = Asset::GetShader("Hdr2CubeMap");
		m_Hdr2CubeMap = new RE::Material(hdr2cubemap);

		Mesh = new Cube();
		BoxMin = glm::vec3(-99999.0);
		BoxMax = glm::vec3(99999.0);

		Material->DepthCompare = GL_LEQUAL;

		// 天空盒禁用剔除
		Material->Cull = false;

		// 阴影接受/生成关闭
		Material->ShadowCast = false;
		Material->ShadowReceive = false;
	}

	SkyBox::~SkyBox()
	{
		delete m_Hdr2CubeMap;
		delete m_CubeMap;
	}

	void SkyBox::SetCubemap(Texture* hdr)
	{
		m_Hdr2CubeMap->SetTexture("hdrMap",hdr,0);

		TextureCube hdrCube;
		hdrCube.DefaultInitialize(128, 128, GL_RGB, GL_FLOAT);

		
	}

	void SkyBox::SetCubemap(TextureCube* cubemap)
	{
		m_CubeMap = cubemap;
		Material->SetTextureCube("skybox", m_CubeMap, 0);
	}
}

