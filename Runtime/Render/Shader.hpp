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

	// Shader一经加载，应该持续到程序结束，不需要显式释放
	class Shader
	{
	private:
		std::string m_Name;
		unsigned int m_ID;

		// TODO: 构建哈希表来代替
		std::vector<Uniform> Uniforms;
		std::vector<VertexAttribute> Attributes;

	public:
		Shader() = default;

		// 常规vs+fs着色器组合
		Shader(std::string name, 
			std::string vsCode, 
			std::string fsCode, 
			// defines 是一组字符串定义
			// 如：defines = {"A","B","C"}
			// 那么，就会在该vs和fs着色器文件中，添加如下定义：
			// #define A
			// #define B
			// #define C
			// 配合glsl本身的 #ifdef / #ifndef 条件宏
			// 实现shader条件编译选项
			std::vector<std::string> defines = std::vector<std::string>());


		void Use();

		// 确认该uniform值是否存在
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
