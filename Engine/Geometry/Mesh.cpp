#include "Mesh.hpp"

namespace Engine
{
	Mesh::Mesh()
	{
		
	}

	Mesh::Mesh(std::vector<glm::vec3> positions,
			   std::vector<unsigned int> indices)
	{
		Positions = positions;
		Indices = indices;
	}

	Mesh::Mesh(std::vector<glm::vec3> positions,
			   std::vector<glm::vec2> uv,
			   std::vector<unsigned int> indices)
	{
		Positions = positions;
		UV = uv;
		Indices = indices;
	}

	Mesh::Mesh(std::vector<glm::vec3> positions,
			   std::vector<glm::vec2> uv,
			   std::vector<glm::vec3> normals,
			   std::vector<unsigned int> indices)
	{
		Positions = positions;
		UV = uv;
		Normals = normals;
		Indices = indices;
	}



}

