#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace RE
{
	enum class TOPOLOGY
	{
		POINTS,
		LINES,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
	};

	// TODO: Mesh加载入内存后 是否需要释放？
	class Mesh
	{
	private:
		unsigned int m_VAO = 0;
		unsigned int m_VBO;
		unsigned int m_EBO;

	public:
		
		std::vector<glm::vec3> Positions;
		std::vector<glm::vec2> UV;
		std::vector<glm::vec3> Normals;
		std::vector<glm::vec3> Tangents;
		std::vector<glm::vec3> Bitangents;

		TOPOLOGY Topology = TOPOLOGY::TRIANGLES;
		std::vector<unsigned int> Indices;

	public:
		Mesh();
		Mesh(std::vector<glm::vec3> positions, std::vector<unsigned int> indices);
		Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<unsigned int> indices);
		Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<unsigned int> indices);
		Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec2> uv, std::vector<glm::vec3> normals, std::vector<glm::vec3> tangents, std::vector<glm::vec3> bitangents, std::vector<unsigned int> indices);

	public:
		// 手动设置顶点数据
		void SetPositions(std::vector<glm::vec3> positions);
		void SetUVs(std::vector<glm::vec2> uv);
		void SetNormals(std::vector<glm::vec3> normals);
		void SetTangents(std::vector<glm::vec3> tangents,std::vector<glm::vec3> bitangents); 

		// 将顶点数据提交到GPU
		void Finalize(bool interleaved = true);
	private:
		friend class Renderer;
	};
}


