#pragma once

#include <glm/glm.hpp>

namespace RE
{
	class CommandBuffer;
	class GraphicCache;
	class Quad;
	class Mesh;
	class Shader;
	class FlyCamera;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Init();
	private:
		// ��Ⱦ��������
		void RenderMesh(Mesh* mesh, Shader* shader);

		// ������Render Command��
		void RenderCustomCommand(RenderCommand* command,FlyCamera* customCamera,bool updateGLSettings = true);

	private:
		CommandBuffer* m_CommandBuffer;
		GraphicCache*  m_GraphicCache;
		glm::vec2 m_RenderSize;
		Quad* m_NDCQuad;
	};

}

