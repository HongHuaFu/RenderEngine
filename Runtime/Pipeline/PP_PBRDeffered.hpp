#pragma once

// PBR延迟渲染管线

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

		bool m_Wireframe = false; // 线框模式渲染？
		bool m_Shadow = true;
		// IBL 所需要的一些预处理材质
		Material* m_IrradianceCapture;
		Material* m_PrefilterCapture;
		Material* m_IntegrateBRDF;

		// BRDF预积分的LUT图
		RenderTarget* m_RenderTargetBRDFLUT;

		// 延时渲染需要使用的GBuffer
		RenderTarget* m_GBuffer;
	};

}

