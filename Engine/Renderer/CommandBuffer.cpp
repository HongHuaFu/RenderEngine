#include "CommandBuffer.hpp"
#include "RenderTarget.hpp"
#include "../Shading/Material.hpp"
#include "../Shading/Shader.hpp"
#include <algorithm>
#include <tuple>

namespace Engine
{
	CommandBuffer::CommandBuffer(Renderer* renderer)
	{
		m_Renderer = renderer;
	}

	CommandBuffer::~CommandBuffer()
	{
		Clear();
	}

	void CommandBuffer::Push(Mesh* mesh, Material* material, 
						     glm::mat4 transform, glm::mat4 prevTransform, 
							 glm::vec3 boxMin, glm::vec3 boxMax, 
							 RenderTarget* target)
	{
		RenderCommand command = {};
		command.Mesh          = mesh;
		command.Material      = material;
		command.Transform     = transform;
		command.PrevTransform = prevTransform;
		command.BoxMin        = boxMin;
		command.BoxMax        = boxMax;

		// 开启混合测试的材质放在Alpha渲染队列中
		if (material->Blend)
		{
			material->Type = MATERIAL_CUSTOM;
			m_AlphaRenderCommands.push_back(command);
		}
		else
		{
			// 检测材质类型
			if (material->Type == MATERIAL_DEFAULT)
			{
				m_DeferredRenderCommands.push_back(command);
			}
			else if (material->Type == MATERIAL_CUSTOM)
			{
				if (m_CustomRenderCommands.find(target) != m_CustomRenderCommands.end())
					m_CustomRenderCommands[target].push_back(command);
				else
				{
					m_CustomRenderCommands[target] = std::vector<RenderCommand>();
					m_CustomRenderCommands[target].push_back(command);
				}
			}
			else if (material->Type == MATERIAL_POST_PROCESS)
			{
				m_PostProcessingRenderCommands.push_back(command);
			}
		}
	}

	void CommandBuffer::Clear()
	{
		m_DeferredRenderCommands.clear();
		m_CustomRenderCommands.clear();
		m_PostProcessingRenderCommands.clear();
		m_AlphaRenderCommands.clear();
	}

	// TODO: 修改为特定类型
	bool renderSortDeferred(const RenderCommand& a, const RenderCommand& b)
	{
		return a.Material->GetShader()->GetID() < b.Material->GetShader()->GetID();
	}

	bool renderSortCustom(const RenderCommand &a, const RenderCommand &b)
	{       
	
		return std::make_tuple(a.Material->Blend, a.Material->GetShader()->GetID()) < 
			std::make_tuple(b.Material->Blend, b.Material->GetShader()->GetID());
	}

	bool renderSortShader(const RenderCommand &a, const RenderCommand &b)
	{
		return a.Material->GetShader()->GetID() < b.Material->GetShader()->GetID();
	}

	void CommandBuffer::Sort()
	{
		std::sort(m_DeferredRenderCommands.begin(), m_DeferredRenderCommands.end(), renderSortDeferred);
		for (auto rtIt = m_CustomRenderCommands.begin(); rtIt != m_CustomRenderCommands.end(); rtIt++) 
		{
			std::sort(rtIt->second.begin(), rtIt->second.end(), renderSortCustom);
		}
	}

	std::vector<RenderCommand> CommandBuffer::GetDeferredRenderCommands(bool cull)
	{
		if (cull)
		{
			std::vector<RenderCommand> commands;
			for (auto it = m_DeferredRenderCommands.begin(); it != m_DeferredRenderCommands.end(); ++it)
			{
				RenderCommand command = *it;
				if (m_Renderer->GetCamera()->Frustum.Intersect(command.BoxMin, command.BoxMax)) {
					commands.push_back(command);
				}
			}
			return commands;
		}
		else
		{
			return m_DeferredRenderCommands;
		}
	}

	std::vector<RenderCommand> CommandBuffer::GetCustomRenderCommands(RenderTarget *target, bool cull)
	{
		
		if (target == nullptr && cull)
		{
			std::vector<RenderCommand> commands;
			for (auto it = m_CustomRenderCommands[target].begin(); it != m_CustomRenderCommands[target].end(); ++it)
			{
				RenderCommand command = *it;
				if (m_Renderer->GetCamera()->Frustum.Intersect(command.BoxMin, command.BoxMax)) {
					commands.push_back(command);
				}
			}
			return commands;
		}
		else
		{
			return m_CustomRenderCommands[target];
		}
	}

	std::vector<RenderCommand> CommandBuffer::GetAlphaRenderCommands(bool cull)
	{
		if (cull)
		{
			std::vector<RenderCommand> commands;
			for (auto it = m_AlphaRenderCommands.begin(); it != m_AlphaRenderCommands.end(); ++it)
			{
				RenderCommand command = *it;
				if (m_Renderer->GetCamera()->Frustum.Intersect(command.BoxMin, command.BoxMax)) {
					commands.push_back(command);
				}
			}
			return commands;
		}
		else
		{
			return m_AlphaRenderCommands;
		}
	}

	std::vector<RenderCommand> CommandBuffer::GetPostProcessingRenderCommands()
	{
		return m_PostProcessingRenderCommands;
	}

	std::vector<RenderCommand> CommandBuffer::GetShadowCastRenderCommands()
	{
		std::vector<RenderCommand> commands;
		for (auto it = m_DeferredRenderCommands.begin(); it != m_DeferredRenderCommands.end(); ++it)
		{
			if (it->Material->ShadowCast)
			{
				commands.push_back(*it);
			}
		}
		for (auto it = m_CustomRenderCommands[nullptr].begin(); it != m_CustomRenderCommands[nullptr].end(); ++it)
		{
			if (it->Material->ShadowCast)
			{
				commands.push_back(*it);
			}
		}
		return commands;
	}
}


