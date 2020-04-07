#ifndef ENGINE_COMMAND_BUFFER_HPP
#define ENGINE_COMMAND_BUFFER_HPP

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include "RenderCommand.hpp"

namespace Engine
{
	class Renderer;
	class Mesh;
	class Material;
	class RenderTarget;

	class CommandBuffer
	{
	private:
		Renderer* m_Renderer;

		std::vector<RenderCommand> m_DeferredRenderCommands;
		std::vector<RenderCommand> m_AlphaRenderCommands;
		std::vector<RenderCommand> m_PostProcessingRenderCommands;
		std::map<RenderTarget*, std::vector<RenderCommand>> m_CustomRenderCommands;
	public:
		 CommandBuffer(Renderer* renderer);
		~CommandBuffer(); 

		void Push(Mesh* mesh, Material* material, 
				  glm::mat4 transform = glm::mat4(), 
				  glm::mat4 prevTransform = glm::mat4(), 
				  glm::vec3 boxMin = glm::vec3(-99999.0f), 
				  glm::vec3 boxMax = glm::vec3(99999.0f), 
				  RenderTarget* target = nullptr);

		void Clear();
		void Sort();

		std::vector<RenderCommand> GetDeferredRenderCommands(bool cull = false);

		std::vector<RenderCommand> GetAlphaRenderCommands(bool cull = false);

		std::vector<RenderCommand> GetCustomRenderCommands(RenderTarget* target, bool cull = false);

		std::vector<RenderCommand> GetPostProcessingRenderCommands();

		std::vector<RenderCommand> GetShadowCastRenderCommands();
	};

}



#endif 
