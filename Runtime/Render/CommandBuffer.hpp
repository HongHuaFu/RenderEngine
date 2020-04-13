#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>

namespace RE
{
	class Mesh;
	class Material;

	// 将Render与场景分隔开来
	// 单次渲染命令
	struct RenderCommand
	{
		glm::mat4 Transform = glm::mat4(1.0f);
		glm::mat4 PrevTransform = glm::mat4(1.0f);

		Mesh* Mesh;
		Material* Material;

		glm::vec3 BoxMin;
		glm::vec3 BoxMax;
	};

	class Renderer;
	class RenderTarget;

	class CommandBuffer
	{
	private:
		Renderer* m_Renderer;

		// 自定义渲染 每次渲染到对应的RenderTarget中
		// 因为是单批次渲染 所以无需区别透明/默认/后处理
		std::map<RenderTarget*, std::vector<RenderCommand>> m_CustomRenderCommands;

		// 透明物体渲染队列
		std::vector<RenderCommand> m_AlphaRenderCommands;

		// 默认渲染队列
		std::vector<RenderCommand> m_DefaultRenderCommands;

		// 后处理渲染队列
		std::vector<RenderCommand> m_PostProcessingRenderCommands;

	public:
		CommandBuffer(Renderer* renderer);
		~CommandBuffer(); 

		void Clear();

		void Push(Mesh* mesh, Material* material, glm::mat4 transform = glm::mat4(1.0f), glm::mat4 prevTransform = glm::mat4(1.0f), glm::vec3 boxMin = glm::vec3(-99999.0f), glm::vec3 boxMax = glm::vec3(99999.0f), RenderTarget* target = nullptr);

		// 获取当前commandbuffer的所有自定义渲染命令 
		std::vector<RenderCommand> GetCustomRenderCommands(RenderTarget *target, bool cull = false);
	};

}