#ifndef ENGINE_MESH_HPP
#define ENGINE_MESH_HPP

#include <vector>
#include <glm/glm.hpp>

namespace Engine
{
	enum TOPOLOGY
	{
		POINTS,
		LINES,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
	};

	class Mesh
	{
	private:
		unsigned int m_VAO = 0;
		unsigned int m_VBO;
		unsigned int m_EBO;

	public:
		// TODO: �����Զ���������uv2��uv3
		std::vector<glm::vec3> Positions;
		std::vector<glm::vec2> UV;
		std::vector<glm::vec3> Normals;
		std::vector<glm::vec3> Tangents;
		std::vector<glm::vec3> Bitangents;

		TOPOLOGY Topology = TRIANGLES;
		std::vector<unsigned int> Indices;

	public:
		Mesh();
		Mesh(std::vector<glm::vec3> positions, 
			 std::vector<unsigned int> indices);

		Mesh(std::vector<glm::vec3> positions, 
			 std::vector<glm::vec2> uv, 
			 std::vector<unsigned int> indices);

		Mesh(std::vector<glm::vec3> positions, 
			 std::vector<glm::vec2> uv, 
			 std::vector<glm::vec3> normals, 
			 std::vector<unsigned int> indices);

		Mesh(std::vector<glm::vec3> positions, 
			 std::vector<glm::vec2> uv, 
			 std::vector<glm::vec3> normals, 
			 std::vector<glm::vec3> tangents, 
			 std::vector<glm::vec3> bitangents, 
			 std::vector<unsigned int> indices);

	public:
		void SetPositions(std::vector<glm::vec3> positions);
		void SetUVs(std::vector<glm::vec2> uv);
		void SetNormals(std::vector<glm::vec3> normals);
		void SetTangents(std::vector<glm::vec3> tangents, 
						 std::vector<glm::vec3> bitangents); 

																							// �����������ύ��GPU
		void Finalize(bool interleaved = true);


	private:
		void CalculateNormals(bool smooth = true);
		void CalculateTangents();
	};
}


#endif 