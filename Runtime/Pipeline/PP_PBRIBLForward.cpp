#include "PP_PBRIBLForward.hpp"

#include "../Render/RenderTarget.hpp"
#include "../Render/Shader.hpp"
#include "../Render//Material.hpp"
#include "../Core/Asset.hpp"

#include "../Geometry/Cube.hpp"
#include "../Render/Mesh.hpp"
#include "../Scene/SceneNode.hpp"
#include "../Render/Renderer.hpp"
#include "../Render/RenderHelper.hpp"
#include "../Render/Texture.hpp"
#include "../Render/TextureCube.hpp"
#include "../Render/CommandBuffer.hpp"
#include "../Render/GraphicsCache.hpp"
#include "../Scene/Camera.hpp"
#include "../Scene/FlyCamera.hpp"


namespace RE
{
	PP_PBRIBLForward::~PP_PBRIBLForward()
	{
		delete m_HdrToCubemap;
		delete m_IrradianceCapture;
		delete m_PrefilterMat;
		delete m_IntegrateBRDF;
		delete m_CubeSceneNode;
		delete m_Cube;
		delete m_SkyBox;
		delete m_Irradiance;
		delete m_Prefiltere;
	}

	void PP_PBRIBLForward::Start(Renderer* renderer)
	{
		m_Renderer = renderer;
		m_IntegrateBRDFLUT = new RenderTarget(128, 128, GL_HALF_FLOAT, 1, true);

		#pragma region ���ʳ�ʼ��
		auto hdrToCubemap = Asset::LoadShader("pbr_ibl_forward::hdr2cubemap","Asset/Shader/PBR_IBL_Forward/Hdr2Cubemap.vs","Asset/Shader/PBR_IBL_Forward/Hdr2Cubemap.fs");
		m_HdrToCubemap = new Material(hdrToCubemap);

		auto irradianceCapture = Asset::LoadShader("pbr_ibl_forward::irradiance","Asset/Shader/PBR_IBL_Forward/Irradiance.vs","Asset/Shader/PBR_IBL_Forward/Irradiance.fs");
		m_IrradianceCapture = new Material(irradianceCapture);

		auto prefilterCapture = Asset::LoadShader("pbr_ibl_forward::prefilter","Asset/Shader/PBR_IBL_Forward/Prefilter.vs","Asset/Shader/PBR_IBL_Forward/Prefilter.fs");
		m_PrefilterMat = new Material(prefilterCapture);

		auto integrateBrdf = Asset::LoadShader("pbr_ibl_forward::integrate","Asset/Shader/PBR_IBL_Forward/IntegrateBrdf.vs","Asset/Shader/PBR_IBL_Forward/IntegrateBrdf.fs");
		m_IntegrateBRDF = new Material(integrateBrdf);

		m_HdrToCubemap->DepthCompare = GL_LEQUAL;
		m_IrradianceCapture->DepthCompare = GL_LEQUAL;
		m_PrefilterMat->DepthCompare  = GL_LEQUAL;
		m_HdrToCubemap->Cull = false;
		m_IrradianceCapture->Cull = false;
		m_PrefilterMat->Cull = false;

		#pragma endregion

		m_Cube = new Cube();

		// ����������SceneNode
		m_CubeSceneNode = new SceneNode(0);
		m_CubeSceneNode->Mesh = m_Cube;
		m_CubeSceneNode->Material = m_HdrToCubemap;

		// ��ȾԤ���� LUT
		renderer->m_RenderHelper->Blit(nullptr,m_IntegrateBRDF, m_IntegrateBRDFLUT);

		Texture* hdrMap = Asset::LoadHDR("MonoLake.hdr", "Asset/Texture/MonoLake.hdr");
		m_SkyBox = HDR2Cubemap(hdrMap);

		// ���ն�ͼԤ����
		m_Irradiance = new TextureCube();
		m_Irradiance->DefaultInitialize(32, 32, GL_RGB, GL_FLOAT);
		m_IrradianceCapture->SetTextureCube("skyboxMap",m_SkyBox,0);
		m_CubeSceneNode->Material = m_IrradianceCapture;
		m_Renderer->m_RenderHelper->RenderToCubeMap(m_CubeSceneNode,m_Irradiance);

		m_Prefiltere = new TextureCube();
		// ��mipmap�ȼ�����������ͼ
		m_Prefiltere->m_FilterMin = GL_LINEAR_MIPMAP_LINEAR;
		m_Prefiltere->DefaultInitialize(128, 128, GL_RGB, GL_FLOAT, true);
		m_PrefilterMat->SetTextureCube("skyboxMap",m_SkyBox,0);
		m_CubeSceneNode->Material = m_PrefilterMat;

		// Ϊÿ��mip�ȼ���Ⱦһ��
		unsigned int maxMipLevels = 5;
		for (unsigned int i = 0; i < maxMipLevels; ++i)
		{
			m_PrefilterMat->SetFloat("roughness", (float)i / (float)(maxMipLevels - 1));
			m_Renderer->m_RenderHelper->RenderToCubeMap(m_CubeSceneNode,m_Prefiltere,glm::vec3(0.0f),i);
		}
	}


	void PP_PBRIBLForward::RenderPushCommand(Renderer* renderer)
	{
		m_Renderer = renderer;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer->m_GraphicCache->SetBlend(false);
		renderer->m_GraphicCache->SetCull(true);
		renderer->m_GraphicCache->SetCullFace(GL_BACK);
		renderer->m_GraphicCache->SetDepthTest(true);
		renderer->m_GraphicCache->SetDepthFunc(GL_LESS);

		// �Զ�����Ⱦ
		renderer->m_RenderTargetsCustom.push_back(nullptr);     
		// ������Ⱦ���е�rendertarget
		for (unsigned int targetIndex = 0; targetIndex < renderer->m_RenderTargetsCustom.size(); ++targetIndex)
		{
			RenderTarget *renderTarget = renderer->m_RenderTargetsCustom[targetIndex];
			if (renderTarget)
			{
				glViewport(0, 0, renderTarget->m_Width, renderTarget->m_Height);
				glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->m_ID);
				if (renderTarget->m_HasDepthAndStencil)
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				else
					glClear(GL_COLOR_BUFFER_BIT);
				renderer->m_Camera->SetPerspective(renderer->m_Camera->FOV, (float)renderTarget->m_Width / (float)renderTarget->m_Height, 0.1, 100.0f); 
			}
			else
			{
				glViewport(0, 0, renderer->m_RenderSize.x, renderer->m_RenderSize.y);
				// ��û��Ŀ������Ⱦ��ͨ��fbo
				//glBindFramebuffer(GL_FRAMEBUFFER, renderer->m_CustomTarget->m_ID);
				glBindFramebuffer(GL_FRAMEBUFFER,0);
				renderer->m_Camera->SetPerspective(renderer->m_Camera->FOV, renderer->m_RenderSize.x / renderer->m_RenderSize.y, 0.1, 100.0f);
			}

			std::vector<RenderCommand> renderCommands = renderer->m_CommandBuffer->GetCustomRenderCommands(renderTarget);

			renderer->m_GraphicCache->SetPolygonMode(renderer->Wireframe ? GL_LINE : GL_FILL);
			// ������rt��������Ⱦ����
			for (unsigned int i = 0; i < renderCommands.size(); ++i)
			{
				// �����������
				renderer->RenderCustomCommand(&renderCommands[i],renderer->GetCamera());
			}
			renderer->m_GraphicCache->SetPolygonMode(GL_FILL);
		}

		renderer->m_CommandBuffer->Clear();
		renderer->m_RenderTargetsCustom.clear();
		renderer->m_CurrentRenderTargetCustom = nullptr;
	}

	TextureCube* PP_PBRIBLForward::HDR2Cubemap(Texture* envMap)
	{
		m_CubeSceneNode->Material = m_HdrToCubemap;
		m_HdrToCubemap->SetTexture("hdrmap", envMap, 0);

		// ʹ��shared_ptr���ð�
		TextureCube* hdrEnvMap = new TextureCube();
		hdrEnvMap->DefaultInitialize(512, 512, GL_RGB, GL_FLOAT);
		m_Renderer->m_RenderHelper->RenderToCubeMap(m_CubeSceneNode, hdrEnvMap);
		return hdrEnvMap;
	}

}