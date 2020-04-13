#include "CommandBuffer.hpp"
#include "Renderer.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "../Scene/Camera.hpp"

#include <algorithm>

namespace RE
{
	CommandBuffer::CommandBuffer(Renderer* renderer)
	{
		m_Renderer = renderer;
	}

	CommandBuffer::~CommandBuffer()
	{
		Clear();
	}

	void CommandBuffer::Clear()
	{
		// 在这里清空所有的容器
		m_DefaultRenderCommands.clear();
		m_CustomRenderCommands.clear();
		m_PostProcessingRenderCommands.clear();
		m_AlphaRenderCommands.clear();
	}

	// 默认渲染管线下的排序
	bool RenderSortDefault(const RenderCommand& a, const RenderCommand& b)
	{
		// 按照shaderID排序
		return a.Material->GetShader()->GetID() < b.Material->GetShader()->GetID();
	}

	// 自定义渲染的排序
	bool RenderSortCustom(const RenderCommand& a, const RenderCommand& b)
	{       
		// 同混合状态下的材质排序
		return std::make_tuple(a.Material->Blend, a.Material->GetShader()->GetID()) < 
			std::make_tuple(b.Material->Blend, b.Material->GetShader()->GetID());
	}

	void CommandBuffer::Sort()
	{
		std::sort(m_DefaultRenderCommands.begin(), m_DefaultRenderCommands.end(), RenderSortDefault);

		//同一个rendertarget下所有的renderCommand排序
		for (auto rtIt = m_CustomRenderCommands.begin(); rtIt != m_CustomRenderCommands.end(); rtIt++) 
		{
			std::sort(rtIt->second.begin(), rtIt->second.end(), RenderSortCustom);
		}
	}

	// 将单个渲染命令提交到渲染队列中
	void CommandBuffer::Push(Mesh* mesh,Material* material,glm::mat4 transform,glm::mat4 prevTransform,glm::vec3 boxMin,glm::vec3 boxMax,RenderTarget* target)
	{
		// 1.构造RenderCommand
		RenderCommand command = {};
		command.Mesh = mesh;
		command.Material = material;
		command.Transform = transform;
		command.PrevTransform = prevTransform;
		command.BoxMin = boxMin;
		command.BoxMax = boxMax;

		// 2.按照材质的类型划分渲染队列

		// 2.1 半透明物体
		if(material->Blend)
		{
			material->Type = MaterialType::CUSTOM;
			m_AlphaRenderCommands.push_back(command);
		}
		else
		{
			// 检测材质类型
			if (material->Type == MaterialType::DEFAULT)
			{
				m_DefaultRenderCommands.push_back(command);
			}
			else if (material->Type == MaterialType::CUSTOM)
			{
				// target == nullptr 的也成一个渲染队列
				if (m_CustomRenderCommands.find(target) != m_CustomRenderCommands.end())
					m_CustomRenderCommands[target].push_back(command);
				else
				{
					m_CustomRenderCommands[target] = std::vector<RenderCommand>();
					m_CustomRenderCommands[target].push_back(command);
				}
			}
			else if (material->Type == MaterialType::POST_PROCESS)
			{
				m_PostProcessingRenderCommands.push_back(command);
			}
		}
	}

	// 获取该RenderTarget对应的渲染命令
	std::vector<RenderCommand> CommandBuffer::GetCustomRenderCommands(RenderTarget* target,bool cull)
	{
		// 开启视锥体剔除
		// TODO: 加入不透明物体排序剔除
		if (target == nullptr && cull)
		{
			
			std::vector<RenderCommand> commands;
			for (auto it = m_CustomRenderCommands[target].begin(); it != m_CustomRenderCommands[target].end(); ++it)
			{
				RenderCommand command = *it;
				// 检测是否与视锥体相交 否则剔除掉，不提交到最终渲染队列中
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

	std::vector<RenderCommand> CommandBuffer::GetDefaultRenderCommands(bool cull)
	{
		if (cull)
		{
			std::vector<RenderCommand> commands;
			for (auto it = m_DefaultRenderCommands.begin(); it != m_DefaultRenderCommands.end(); ++it)
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
			return m_DefaultRenderCommands;
		}
	}

	std::vector<RenderCommand> CommandBuffer::GetAlphaRenderCommands(bool cull)
	{
		
		if (cull)
		{
			// 视锥剔除
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
		// 因为视锥体外的物体 也可能会对视锥体内阴影生成产生影响
		// 所以没有CPU端的视锥剔除

		std::vector<RenderCommand> commands;
		// 先遍历默认的渲染命令 取出产生阴影的渲染命令
		for (auto it = m_DefaultRenderCommands.begin(); it != m_DefaultRenderCommands.end(); ++it)
		{
			if (it->Material->ShadowCast)
			{
				commands.push_back(*it);
			}
		}

		// 遍历自定义渲染队列中 产生阴影的命令
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