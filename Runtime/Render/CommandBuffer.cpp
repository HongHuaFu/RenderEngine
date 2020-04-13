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
		// ������������е�����
		m_DefaultRenderCommands.clear();
		m_CustomRenderCommands.clear();
		m_PostProcessingRenderCommands.clear();
		m_AlphaRenderCommands.clear();
	}

	// Ĭ����Ⱦ�����µ�����
	bool RenderSortDefault(const RenderCommand& a, const RenderCommand& b)
	{
		// ����shaderID����
		return a.Material->GetShader()->GetID() < b.Material->GetShader()->GetID();
	}

	// �Զ�����Ⱦ������
	bool RenderSortCustom(const RenderCommand& a, const RenderCommand& b)
	{       
		// ͬ���״̬�µĲ�������
		return std::make_tuple(a.Material->Blend, a.Material->GetShader()->GetID()) < 
			std::make_tuple(b.Material->Blend, b.Material->GetShader()->GetID());
	}

	void CommandBuffer::Sort()
	{
		std::sort(m_DefaultRenderCommands.begin(), m_DefaultRenderCommands.end(), RenderSortDefault);

		//ͬһ��rendertarget�����е�renderCommand����
		for (auto rtIt = m_CustomRenderCommands.begin(); rtIt != m_CustomRenderCommands.end(); rtIt++) 
		{
			std::sort(rtIt->second.begin(), rtIt->second.end(), RenderSortCustom);
		}
	}

	// ��������Ⱦ�����ύ����Ⱦ������
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

	// ��ȡ��RenderTarget��Ӧ����Ⱦ����
	std::vector<RenderCommand> CommandBuffer::GetCustomRenderCommands(RenderTarget* target,bool cull)
	{
		// ������׶���޳�
		// TODO: ���벻͸�����������޳�
		if (target == nullptr && cull)
		{
			
			std::vector<RenderCommand> commands;
			for (auto it = m_CustomRenderCommands[target].begin(); it != m_CustomRenderCommands[target].end(); ++it)
			{
				RenderCommand command = *it;
				// ����Ƿ�����׶���ཻ �����޳��������ύ��������Ⱦ������
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
			// ��׶�޳�
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
		// ��Ϊ��׶��������� Ҳ���ܻ����׶������Ӱ���ɲ���Ӱ��
		// ����û��CPU�˵���׶�޳�

		std::vector<RenderCommand> commands;
		// �ȱ���Ĭ�ϵ���Ⱦ���� ȡ��������Ӱ����Ⱦ����
		for (auto it = m_DefaultRenderCommands.begin(); it != m_DefaultRenderCommands.end(); ++it)
		{
			if (it->Material->ShadowCast)
			{
				commands.push_back(*it);
			}
		}

		// �����Զ�����Ⱦ������ ������Ӱ������
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