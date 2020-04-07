#ifndef ENGINE_RENDER_COMMAND_HPP
#define ENGINE_RENDER_COMMAND_HPP

#include <glm/glm.hpp>

namespace Engine
{
	class Mesh;
	class Material;
	
	struct RenderCommand
	{
		glm::mat4 Transform;
		glm::mat4 PrevTransform;

		Mesh*      Mesh;
		Material*  Material;

		glm::vec3 BoxMin;
		glm::vec3 BoxMax;
	};
}


#endif // !ENGINE_RENDER_COMMAND_HPP
