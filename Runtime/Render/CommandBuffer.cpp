#include "CommandBuffer.hpp"
#include "Renderer.hpp"
#include "Material.hpp"


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

	std::vector<RenderCommand> CommandBuffer::GetCustomRenderCommands(RenderTarget* target,bool cull)
	{
		// 开启视锥体剔除
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
}