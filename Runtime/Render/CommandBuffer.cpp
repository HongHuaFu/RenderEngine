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
		// ������������е�����
		m_DefaultRenderCommands.clear();
		m_CustomRenderCommands.clear();
		m_PostProcessingRenderCommands.clear();
		m_AlphaRenderCommands.clear();
	}

	void CommandBuffer::Push(Mesh* mesh,Material* material,glm::mat4 transform,glm::mat4 prevTransform,glm::vec3 boxMin,glm::vec3 boxMax,RenderTarget* target)
	{
		// 1.����RenderCommand
		RenderCommand command = {};
		command.Mesh = mesh;
		command.Material = material;
		command.Transform = transform;
		command.PrevTransform = prevTransform;
		command.BoxMin = boxMin;
		command.BoxMax = boxMax;

		// 2.���ղ��ʵ����ͻ�����Ⱦ����

		// 2.1 ��͸������
		if(material->Blend)
		{
			material->Type = MaterialType::CUSTOM;
			m_AlphaRenderCommands.push_back(command);
		}
		else
		{
			// ����������
			if (material->Type == MaterialType::DEFAULT)
			{
				m_DefaultRenderCommands.push_back(command);
			}
			else if (material->Type == MaterialType::CUSTOM)
			{
				// target == nullptr ��Ҳ��һ����Ⱦ����
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
		// ������׶���޳�
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