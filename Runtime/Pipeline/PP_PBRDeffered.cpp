#include "PP_PBRDeffered.hpp"
#include "../Render/Shader.hpp"
#include "../Render/Material.hpp"
#include "../Core/Asset.hpp"
#include "../Render/Renderer.hpp"
#include "../Render/CommandBuffer.hpp"
#include "../Render/GraphicsCache.hpp"
#include "../Render/RenderTarget.hpp"
#include "../Scene/Light.hpp"


namespace RE
{
	void PP_PBRDeffered::Start(Renderer* renderer)
	{
		// 1. ����PBR��Ⱦ��������Ҫ��shader
		Shader* integrateBrdf = Asset::LoadShader("PBR_IntegrateBrdf","Asset/Shader/PBR/IntegrateBRDF.vs","Asset/Shader/PBR/IntegrateBRDF.fs");
	}

	// PBR�ӳ���Ⱦ����
	void PP_PBRDeffered::RenderPushCommand(Renderer* renderer)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer->m_CommandBuffer->Sort();

		// 1.����Ĭ�ϵ���Ⱦ״̬
		renderer->m_GraphicCache->SetBlend(false);
		renderer->m_GraphicCache->SetCull(true);
		renderer->m_GraphicCache->SetCullFace(GL_BACK);
		renderer->m_GraphicCache->SetDepthTest(true);
		renderer->m_GraphicCache->SetDepthFunc(GL_LESS);

		// 2.����ȫ��UBO
		renderer->UpdateGlobalUBO();

		// 3.��Ⱦ��GBuffer
		// ��ȡ���й���Ĭ�ϵ���Ⱦ����
		// �ڴ˹���������ʱ��Ⱦ
		std::vector<RenderCommand> deferredRenderCommands = renderer->m_CommandBuffer->GetDefaultRenderCommands(true);

		glViewport(0, 0, renderer->m_RenderSize.x, renderer->m_RenderSize.y);

		// ��GBuffer FBO
		glBindFramebuffer(GL_FRAMEBUFFER, m_GBuffer->GetID());
		unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, 
										GL_COLOR_ATTACHMENT1, 
										GL_COLOR_ATTACHMENT2, 
										GL_COLOR_ATTACHMENT3 };
		// ʹ��4����ɫ
		glDrawBuffers(4, attachments);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer->m_GraphicCache->SetPolygonMode(m_Wireframe ? GL_LINE : GL_FILL);
		for (unsigned int i = 0; i < deferredRenderCommands.size(); ++i)
		{
			// ʹ����ǰ���µ�UBO��������Ⱦ
			renderer->RenderCustomCommand(&deferredRenderCommands[i], nullptr, false);
		}
		renderer->m_GraphicCache->SetPolygonMode(GL_FILL);

		// TODO: ���룺 3.��Ⱦ��Ӱ
		// TODO: ����
		attachments[0] = GL_COLOR_ATTACHMENT0;
		glDrawBuffers(4, attachments);
	}

}
