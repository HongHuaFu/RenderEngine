#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>

namespace RE
{
	class Mesh;
	class Material;

	// ��Render�볡���ָ�����
	// ������Ⱦ����
	struct RenderCommand
	{
		glm::mat4 Transform = glm::mat4(1.0f);
		glm::mat4 PrevTransform = glm::mat4(1.0f);

		Mesh* Mesh;
		Material* Material;

		// ������׶�޳��ȵ�
		glm::vec3 BoxMin;
		glm::vec3 BoxMax;
	};

	class Renderer;
	class RenderTarget;

	class CommandBuffer
	{
	private:
		Renderer* m_Renderer;

		// �Զ�����Ⱦ ÿ����Ⱦ����Ӧ��RenderTarget��
		// ��Ϊ�ǵ�������Ⱦ ������������͸��/Ĭ��/����
		std::map<RenderTarget*, std::vector<RenderCommand>> m_CustomRenderCommands;

		// ͸��������Ⱦ����
		std::vector<RenderCommand> m_AlphaRenderCommands;

		// Ĭ����Ⱦ����
		std::vector<RenderCommand> m_DefaultRenderCommands;

		// ������Ⱦ����
		std::vector<RenderCommand> m_PostProcessingRenderCommands;

	public:
		CommandBuffer(Renderer* renderer);
		~CommandBuffer(); 

		void Clear();
		void Sort();

		void Push(Mesh* mesh, Material* material, glm::mat4 transform = glm::mat4(1.0f), glm::mat4 prevTransform = glm::mat4(1.0f), glm::vec3 boxMin = glm::vec3(-99999.0f), glm::vec3 boxMax = glm::vec3(99999.0f), RenderTarget* target = nullptr);

		// ��ȡ��ǰrender target�������Զ�����Ⱦ�������
		std::vector<RenderCommand> GetCustomRenderCommands(RenderTarget *target, bool cull = false);

		// ��ȡĬ����Ⱦ�������
		std::vector<RenderCommand> GetDefaultRenderCommands(bool cull = false);

		// ��ȡ��͸��������Ⱦ����
		// TODO����͸���������ӰͶ������ܣ�
		std::vector<RenderCommand> GetAlphaRenderCommands(bool cull = false);

		// ȡ�����еĺ�����Ⱦ�������
		std::vector<RenderCommand> GetPostProcessingRenderCommands();

		// ȡ������Ͷ����Ӱ����Ⱦ�������
		std::vector<RenderCommand> GetShadowCastRenderCommands();
	};

}