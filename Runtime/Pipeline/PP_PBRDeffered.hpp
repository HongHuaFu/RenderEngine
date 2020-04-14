#pragma once

// PBR�ӳ���Ⱦ����

#include "../Render/Pipeline.hpp"

#include <vector>
#include <glm/glm.hpp>

namespace RE
{
	class Material;
	class RenderTarget;
	class DirectionalLight;
	class PointLight;

	class PP_PBRDeffered : public Pipeline
	{
	public:
		virtual void Start(Renderer* renderer) override;
		virtual void RenderPushCommand(Renderer* renderer) override;

	private:

		std::vector<DirectionalLight*> m_DirectionalLights;
		std::vector<PointLight*> m_PointLights;

		std::vector<RenderTarget*> m_ShadowRenderTargets;
		std::vector<glm::mat4> m_ShadowViewProjections;

		bool m_Wireframe = false; // �߿�ģʽ��Ⱦ��
		bool m_Shadow = true;
		// IBL ����Ҫ��һЩԤ�������
		Material* m_IrradianceCapture;
		Material* m_PrefilterCapture;
		Material* m_IntegrateBRDF;

		// BRDFԤ���ֵ�LUTͼ
		RenderTarget* m_RenderTargetBRDFLUT;

		// ��ʱ��Ⱦ��Ҫʹ�õ�GBuffer
		RenderTarget* m_GBuffer;
	};

}

