#include "PP_Defferd_Lambert.hpp"
#include <glad/glad.h>

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
	void PP_Defferd_Lambert::Start(Renderer* renderer)
	{
		m_Renderer = renderer;
	}

	void PP_Defferd_Lambert::RenderPushCommand(Renderer* renderer)
	{
		m_Renderer = renderer;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Renderer->m_CommandBuffer->Sort();

		// 设置默认的渲染状态
		renderer->m_GraphicCache->SetBlend(false);
		renderer->m_GraphicCache->SetCull(true);
		renderer->m_GraphicCache->SetCullFace(GL_BACK);
		renderer->m_GraphicCache->SetDepthTest(true);
		renderer->m_GraphicCache->SetDepthFunc(GL_LESS);

		// 渲染到GBuffer
		auto defaultCommands = m_Renderer->m_CommandBuffer->GetDefaultRenderCommands(true);
		glViewport(0, 0, m_Renderer->m_RenderSize.x, m_Renderer->m_RenderSize.y);

		glBindFramebuffer(GL_FRAMEBUFFER, m_Renderer->m_GBuffer->GetID());
		unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(4, attachments);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer->m_GraphicCache->SetPolygonMode( m_Renderer->Wireframe ? GL_LINE : GL_FILL);

		for (unsigned int i = 0; i < defaultCommands.size(); ++i)
		{
			m_Renderer->RenderCustomCommand(&defaultCommands[i], nullptr, false);
		}

		renderer->m_GraphicCache->SetPolygonMode(GL_FILL);

		// TODO: 加入阴影

		// 灯光Pass
		// 渲染到




		// 自定义渲染
		renderer->m_RenderTargetsCustom.push_back(nullptr);     
		// 遍历渲染所有的rendertarget
		for (unsigned int targetIndex = 0; targetIndex < renderer->m_RenderTargetsCustom.size(); ++targetIndex)
		{
			RenderTarget *renderTarget = renderer->m_RenderTargetsCustom[targetIndex];
			if (renderTarget)
			{
				// TODO:
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
				// 若没有目标则渲染到通用fbo
				glBindFramebuffer(GL_FRAMEBUFFER, renderer->m_CustomTarget->m_ID);
				if (renderer->m_CustomTarget->m_HasDepthAndStencil)
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				else
					glClear(GL_COLOR_BUFFER_BIT);
				renderer->m_Camera->SetPerspective(renderer->m_Camera->FOV, renderer->m_RenderSize.x / renderer->m_RenderSize.y, 0.1, 100.0f);
			}

			std::vector<RenderCommand> renderCommands = renderer->m_CommandBuffer->GetCustomRenderCommands(renderTarget);

			renderer->m_GraphicCache->SetPolygonMode(renderer->Wireframe ? GL_LINE : GL_FILL);
			// 遍历该rt的所有渲染命令
			for (unsigned int i = 0; i < renderCommands.size(); ++i)
			{
				// 加入相机更新
				renderer->RenderCustomCommand(&renderCommands[i],renderer->GetCamera());
			}
			renderer->m_GraphicCache->SetPolygonMode(GL_FILL);
		}

		renderer->m_CommandBuffer->Clear();
		renderer->m_RenderTargetsCustom.clear();
		renderer->m_CurrentRenderTargetCustom = nullptr;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


	}

}

