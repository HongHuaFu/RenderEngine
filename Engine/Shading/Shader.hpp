#ifndef ENGINE_SHADER_HPP
#define ENGINE_SHADER_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "ShaderType.hpp"

namespace Engine
{
	// TODO: 改成智能指针+RAII的内存管理组合
	class Shader
	{
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

		void SetInt   (std::string location, int value);
		void SetBool  (std::string location, bool value);
		void SetFloat (std::string location, float value);

		void SetVector(std::string location, glm::vec2  value);
		void SetVector(std::string location, glm::vec3  value);
		void SetVector(std::string location, glm::vec4  value);

		void SetVectorArray(std::string location, int size, const std::vector<glm::vec2>& values);
		void SetVectorArray(std::string location, int size, const std::vector<glm::vec3>& values);
		void SetVectorArray(std::string location, int size, const std::vector<glm::vec4>& values);

		void SetMatrix(std::string location, glm::mat2 value);
		void SetMatrix(std::string location, glm::mat3 value);
		void SetMatrix(std::string location, glm::mat4 value);

		// TODO: 完成函数体
		void SetMatrixArray(std::string location, int size, glm::mat2* values);
		void SetMatrixArray(std::string location, int size, glm::mat3* values);
		void SetMatrixArray(std::string location, int size, glm::mat4* values);

	public:
		inline unsigned int GetID() const { return m_ID; }
	private:
		int GetUniformLocation(std::string name);

	private:
		std::string m_Name;
		unsigned int m_ID;

		// TODO: 使用字典代替
		std::vector<Uniform>         Uniforms;
		std::vector<VertexAttribute> Attributes;
	};
}

#endif 
