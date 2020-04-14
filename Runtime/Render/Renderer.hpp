#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace RE
{
	class CommandBuffer;
	class GraphicCache;
	class Quad;
	class Mesh;
	class Shader;
	class Camera;
	class FlyCamera;
	class RenderCommand;
	class SceneNode;
	class Material;
	class Pipeline;
	class RenderHelper;
	class PP_PBRIBLForward;
	class RenderTarget;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		
		void Init();
		Camera* GetCamera();

		void SetRenderSize(unsigned int width, unsigned int height);
		glm::vec2 GetRenderSize();

		void PushRender(Mesh* mesh, Material* material, glm::mat4 transform = glm::mat4(), glm::mat4 prevFrameTransform = glm::mat4());
		void PushRender(SceneNode* node);
		void RenderPushedCommands(Pipeline* pipeline);
		
	private:
		// 渲染单个网格
		void RenderMesh(Mesh* mesh, Shader* shader);
		

		// 处理单次Render Command。
		void RenderCustomCommand(RenderCommand* command,Camera* customCamera,bool updateGLSettings = true,bool isSkybox = false);

		void UpdateGlobalUBO();

		// 获取当前激活的RenderTarget
		inline RenderTarget* GetCurrentRenderTarget(){ return m_CurrentRenderTargetCustom; }
		
	public:
		CommandBuffer* m_CommandBuffer;
		GraphicCache* m_GraphicCache;
		glm::vec2 m_RenderSize;
		FlyCamera* m_Camera;
		PP_PBRIBLForward* m_PP_PBRIBLForward;
		RenderTarget* m_CurrentRenderTargetCustom;
		RenderHelper* m_RenderHelper;
		std::vector<RenderTarget*> m_RenderTargetsCustom;
		RenderTarget* m_CustomTarget;

	public://开关
		bool OpenShadow = true;
		bool Wireframe = false;
	private:
		friend class RenderHelper;

	private:
		friend class PP_PBRDeffered;
		friend class PP_PBRIBLForward;
	};

}

