#pragma once

#include "../Render/Mesh.hpp"

namespace RE
{
	// -1f +1fКазг,
	class Cube1 : public Mesh
	{
	public:
		Cube1()
		{
			Positions = std::vector<glm::vec3> 
			{
				glm::vec3(-1.0f, -1.0f, -1.0f),
				glm::vec3( 1.0f,  1.0f, -1.0f), 
				glm::vec3( 1.0f, -1.0f, -1.0f), 
				glm::vec3( 1.0f,  1.0f, -1.0f), 
				glm::vec3(-1.0f, -1.0f, -1.0f),
				glm::vec3(-1.0f,  1.0f, -1.0f),

				glm::vec3(-1.0f, -1.0f,  1.0f),
				glm::vec3( 1.0f, -1.0f,  1.0f),
				glm::vec3( 1.0f,  1.0f,  1.0f),
				glm::vec3( 1.0f,  1.0f,  1.0f), 
				glm::vec3(-1.0f,  1.0f,  1.0f),
				glm::vec3(-1.0f, -1.0f,  1.0f),

				glm::vec3(-1.0f,  1.0f,  1.0f),
				glm::vec3(-1.0f,  1.0f, -1.0f),
				glm::vec3(-1.0f, -1.0f, -1.0f),
				glm::vec3(-1.0f, -1.0f, -1.0f),
				glm::vec3(-1.0f, -1.0f,  1.0f),
				glm::vec3(-1.0f,  1.0f,  1.0f),

				glm::vec3( 1.0f,  1.0f,  1.0f), 
				glm::vec3( 1.0f, -1.0f, -1.0f), 
				glm::vec3( 1.0f,  1.0f, -1.0f), 
				glm::vec3( 1.0f, -1.0f, -1.0f), 
				glm::vec3( 1.0f,  1.0f,  1.0f), 
				glm::vec3( 1.0f, -1.0f,  1.0f), 

				glm::vec3(-1.0f, -1.0f, -1.0f),
				glm::vec3( 1.0f, -1.0f, -1.0f),
				glm::vec3( 1.0f, -1.0f,  1.0f),
				glm::vec3( 1.0f, -1.0f,  1.0f), 
				glm::vec3(-1.0f, -1.0f,  1.0f),
				glm::vec3(-1.0f, -1.0f, -1.0f),

				glm::vec3(-1.0f,  1.0f, -1.0f),
				glm::vec3( 1.0f,  1.0f, 1.0f), 
				glm::vec3( 1.0f,  1.0f, -1.0f), 
				glm::vec3( 1.0f,  1.0f,  1.0f), 
				glm::vec3(-1.0f,  1.0f, -1.0f),
				glm::vec3(-1.0f,  1.0f, 1.0f),
			};
			UV = std::vector<glm::vec2> 
			{
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),

				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),

				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),

				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 0.0f),

				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),

				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
			};
			Normals = std::vector<glm::vec3>
			{
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),

				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),

				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),

				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),

				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),

				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
			};

			Topology = TOPOLOGY::TRIANGLES;
			Finalize();
		}
	};

	// -0.5f +0.5fКазг,
	class Cube : public Mesh
	{
	public:
		Cube()
		{
			Positions = std::vector<glm::vec3> 
			{
				glm::vec3(-0.5f, -0.5f, -0.5f),
				glm::vec3( 0.5f,  0.5f, -0.5f), 
				glm::vec3( 0.5f, -0.5f, -0.5f), 
				glm::vec3( 0.5f,  0.5f, -0.5f), 
				glm::vec3(-0.5f, -0.5f, -0.5f),
				glm::vec3(-0.5f,  0.5f, -0.5f),

				glm::vec3(-0.5f, -0.5f,  0.5f),
				glm::vec3( 0.5f, -0.5f,  0.5f),
				glm::vec3( 0.5f,  0.5f,  0.5f),
				glm::vec3( 0.5f,  0.5f,  0.5f), 
				glm::vec3(-0.5f,  0.5f,  0.5f),
				glm::vec3(-0.5f, -0.5f,  0.5f),

				glm::vec3(-0.5f,  0.5f,  0.5f),
				glm::vec3(-0.5f,  0.5f, -0.5f),
				glm::vec3(-0.5f, -0.5f, -0.5f),
				glm::vec3(-0.5f, -0.5f, -0.5f),
				glm::vec3(-0.5f, -0.5f,  0.5f),
				glm::vec3(-0.5f,  0.5f,  0.5f),

				glm::vec3( 0.5f,  0.5f,  0.5f), 
				glm::vec3( 0.5f, -0.5f, -0.5f), 
				glm::vec3( 0.5f,  0.5f, -0.5f), 
				glm::vec3( 0.5f, -0.5f, -0.5f), 
				glm::vec3( 0.5f,  0.5f,  0.5f), 
				glm::vec3( 0.5f, -0.5f,  0.5f), 

				glm::vec3(-0.5f, -0.5f, -0.5f),
				glm::vec3( 0.5f, -0.5f, -0.5f),
				glm::vec3( 0.5f, -0.5f,  0.5f),
				glm::vec3( 0.5f, -0.5f,  0.5f), 
				glm::vec3(-0.5f, -0.5f,  0.5f),
				glm::vec3(-0.5f, -0.5f, -0.5f),

				glm::vec3(-0.5f,  0.5f, -0.5f),
				glm::vec3( 0.5f,  0.5f,  0.5f), 
				glm::vec3( 0.5f,  0.5f, -0.5f), 
				glm::vec3( 0.5f,  0.5f,  0.5f), 
				glm::vec3(-0.5f,  0.5f, -0.5f),
				glm::vec3(-0.5f,  0.5f,  0.5f),
			};
			UV = std::vector<glm::vec2> 
			{
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),

				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),

				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),

				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 0.0f),

				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),

				glm::vec2(0.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(1.0f, 1.0f),
				glm::vec2(1.0f, 0.0f),
				glm::vec2(0.0f, 1.0f),
				glm::vec2(0.0f, 0.0f),
			};
			Normals = std::vector<glm::vec3>
			{
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),
				glm::vec3( 0.0f,  0.0f, -1.0f),

				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),
				glm::vec3( 0.0f,  0.0f,  1.0f),

				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),
				glm::vec3(-1.0f,  0.0f,  0.0f),

				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),
				glm::vec3( 1.0f,  0.0f,  0.0f),

				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),
				glm::vec3( 0.0f, -1.0f,  0.0f),

				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
				glm::vec3( 0.0f,  1.0f,  0.0f),
			};

			Topology = TOPOLOGY::TRIANGLES;
			Finalize();
		}
	};

}

