#pragma once

#include "../Render/Pipeline.hpp"

// «∞œÚ‰÷»æ
// IBLπ‚’’

namespace RE
{
	class Material;
	class RenderTarget;
	class Mesh;
	class SceneNode;
	class TextureCube;
	class Texture;

	class PP_PBRIBLForward : public Pipeline
	{
	public:
		virtual void Start(Renderer* renderer) override;
		virtual void RenderPushCommand(Renderer* renderer) override;
	private:
		TextureCube* HDR2Cubemap(Texture* envMap);

	private:
		Renderer* m_Renderer;
		Material* m_HdrToCubemap;
		Material* m_IrradianceCapture;
		Material* m_Prefilter;
		Material* m_IntegrateBRDF;

		Mesh* m_Cube;
		SceneNode* m_CubeSceneNode;

		RenderTarget* m_IntegrateBRDFLUT;
		TextureCube* m_SkyBox;
		TextureCube* m_Irradiance;
		TextureCube* m_Prefiltered;

		unsigned int m_CaptureFBO;
	public:
		~PP_PBRIBLForward();
		TextureCube* GetSkyBoxCubemap(){ return m_SkyBox; }
	};
}