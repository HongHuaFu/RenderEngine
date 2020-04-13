#pragma once

#include <glm/glm.hpp>

namespace RE
{
	class CommandBuffer;
	class GraphicCache;
	class Quad;
	class Mesh;
	class Shader;
	class Camera;
	class RenderCommand;
	class SceneNode;
	class Material;
	class Pipeline;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		
		void Init();
		Camera* GetCamera();

		void PushRender(Mesh* mesh, Material* material, glm::mat4 transform = glm::mat4(), glm::mat4 prevFrameTransform = glm::mat4());
		void PushRender(SceneNode* node);
	private:
		// ��Ⱦ��������
		void RenderMesh(Mesh* mesh, Shader* shader);
		void RenderPushedCommands(Pipeline* pipeline);
		// ������Render Command��
		void RenderCustomCommand(RenderCommand* command,Camera* customCamera,bool updateGLSettings = true);

		// ��ȡ��ǰ�����RenderTarget
		inline RenderTarget* GetCurrentRenderTarget(){ return m_CurrentRenderTargetCustom; }
		
	private:
		CommandBuffer* m_CommandBuffer;
		GraphicCache*  m_GraphicCache;
		glm::vec2 m_RenderSize;
		Camera* m_Camera;
		Pipeline* m_PBRPipeline;
		RenderTarget* m_CurrentRenderTargetCustom = nullptr;

	public://����
		bool OpenShadow = true;
	private:
		friend class RenderHelper;
		friend class Pipeline;
	};

}

