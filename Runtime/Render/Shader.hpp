#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace RE
{	
	enum class Shader_Type
	{
		BOOL,
		INT,
		FLOAT,
		SAMPLER1D,
		SAMPLER2D,
		SAMPLER3D,
		SAMPLERCUBE,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4
	};

	struct Uniform
	{
		Shader_Type Type;
		std::string Name;
		int Size;
		unsigned int Location;
	};

	struct VertexAttribute
	{
		Shader_Type Type;
		std::string Name;
		int Size;
		unsigned int Location;
	};

	// Shaderһ�����أ�Ӧ�ó������������������Ҫ��ʽ�ͷ�
	class Shader
	{
	private:
		std::string m_Name;
		unsigned int m_ID;

		// TODO: ������ϣ��������
		std::vector<Uniform> Uniforms;
		std::vector<VertexAttribute> Attributes;

	public:
		Shader() = default;

		// ����vs+fs��ɫ�����
		Shader(std::string name, 
			std::string vsCode, 
			std::string fsCode, 
			// defines ��һ���ַ�������
			// �磺defines = {"A","B","C"}
			// ��ô���ͻ��ڸ�vs��fs��ɫ���ļ��У�������¶��壺
			// #define A
			// #define B
			// #define C
			// ���glsl����� #ifdef / #ifndef ������
			// ʵ��shader��������ѡ��
			std::vector<std::string> defines = std::vector<std::string>());


		void Use();

		// ȷ�ϸ�uniformֵ�Ƿ����
		bool HasUniform(std::string name);

	public: // setter

		void SetInt(std::string location, int value);
		void SetBool(std::string location, bool value);
		void SetFloat(std::string location, float value);

		void SetVector(std::string location, glm::vec2 value);
		void SetVector(std::string location, glm::vec3 value);
		void SetVector(std::string location, glm::vec4 value);

		void SetVectorArray(std::string location, int size, const std::vector<glm::vec2>& values);
		void SetVectorArray(std::string location, int size, const std::vector<glm::vec3>& values);
		void SetVectorArray(std::string location, int size, const std::vector<glm::vec4>& values);

		void SetMatrix(std::string location, glm::mat2 value);
		void SetMatrix(std::string location, glm::mat3 value);
		void SetMatrix(std::string location, glm::mat4 value);

	public:
		inline unsigned int GetID() const { return m_ID; }
	private:
		int GetUniformLocation(std::string name);
	};
}
