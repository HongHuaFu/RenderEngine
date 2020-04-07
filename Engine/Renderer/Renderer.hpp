#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include <glm/glm.hpp>

#include "CommandBuffer.hpp"
#include "GraphicCache.hpp"
#include "MaterialLibrary.hpp"
#include "../Scene/Camera.hpp"

namespace Engine
{
	class Renderer
	{
	public:
		Renderer() = default;
		void Init();
	private:
		// render state
		CommandBuffer* m_CommandBuffer;
		GraphicCache m_GLCache;
		glm::vec2 m_RenderSize;

		// materials
		MaterialLibrary* m_MaterialLibrary;

		// camera
		Camera* m_Camera;
		glm::mat4 m_PrevViewProjection;


	};
}


#endif // !ENGINE_RENDERER_HPP
