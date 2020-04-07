#ifndef ENGINE_SHADER_HPP
#define ENGINE_SHADER_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "ShaderType.hpp"

namespace Engine
{
	// TODO: �ĳ�����ָ��+RAII���ڴ�������
	class Shader
	{
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

		// TODO: ��ɺ�����
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

		// TODO: ʹ���ֵ����
		std::vector<Uniform>         Uniforms;
		std::vector<VertexAttribute> Attributes;
	};
}

#endif 
