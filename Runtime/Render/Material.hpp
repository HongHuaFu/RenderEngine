#pragma once

// ����ϵͳ
// �洢Uniform�Ͳ�������ֵ
// ÿһ��SceneNode�������ٰ���һ�����ʣ��ύ����Ⱦ�����ʱ��
// ����������ʵ�Uniform/����������
// ���޸Ķ�Ӧ��Shader���

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace RE
{
	class Shader;
	class Texture;
	class TextureCube;
	
	enum class Shader_Type;
	struct UniformValue
	{
		Shader_Type Type;
		union
		{
			bool Bool;
			int Int;
			float Float;

			glm::vec2 Vec2;
			glm::vec3 Vec3;
			glm::vec4 Vec4;
			glm::mat2 Mat2;
			glm::mat3 Mat3;
			glm::mat4 Mat4;
		};

		UniformValue() {}
	};

	struct UniformValueSampler
	{
		Shader_Type Type;
		unsigned int Unit;
		union 
		{
			Texture *Texture;
			TextureCube *TextureCube;
		};

		UniformValueSampler() {}
	};

	enum class MaterialType
	{
		DEFAULT, // ��ǰ�����µ�Ĭ�ϲ���
		CUSTOM,  // ��ǰ�����µ��Զ������
		POST_PROCESS, // �������
	};

	class Material
	{
	public:
		Material();
		Material(Shader* shader);

		Shader* GetShader();
		void SetShader(Shader* shader);

		Material Copy();

		// ���õ�ʱ�򣬰�uniform���͸���Ϊ��ȷ��ֵ
		void SetBool(std::string name,bool value);
		void SetInt(std::string name,int value);
		void SetFloat(std::string name,float value);
		void SetTexture(std::string name,Texture* value, unsigned int unit = 0);
		void SetTextureCube(std::string name, TextureCube* value, unsigned int unit = 0);
		void SetVector(std::string name,glm::vec2 value);
		void SetVector(std::string name,glm::vec3 value);
		void SetVector(std::string name,glm::vec4 value);
		void SetMatrix(std::string name,glm::mat2 value);
		void SetMatrix(std::string name,glm::mat3 value);
		void SetMatrix(std::string name,glm::mat4 value);

	
		std::map<std::string, UniformValue>* GetUniforms();
		std::map<std::string, UniformValueSampler>* GetSamplerUniforms();


	private:
		Shader* m_Shader; 

		// �����ò���ֵ��ʱ�����ɢ�б�
		// û������ֵ�Ͳ���д�����

		// ������ǰ���ʽ�����Ⱦ����ʱ��Ⱦ���Ż����m_Uniforms��m_SamplerUniforms��ֵ��Shader��
		std::map<std::string, UniformValue> m_Uniforms;
		std::map<std::string, UniformValueSampler> m_SamplerUniforms; 

	public:
		// Ĭ�ϲ�����������Ϊ�Զ���
		MaterialType Type = MaterialType::CUSTOM;
		glm::vec4 Color = glm::vec4(1.0f);

		// ���
		bool DepthTest = true;
		bool DepthWrite = true;

		unsigned int DepthCompare = GL_LESS;

		// ���޳�
		bool Cull = true;
		unsigned int CullFace = GL_BACK;
		unsigned int CullWindingOrder = GL_CCW;

		// ���
		bool Blend = false;
		unsigned int BlendSrc = GL_ONE; 
		unsigned int BlendDst = GL_ONE_MINUS_SRC_ALPHA;
		unsigned int BlendEquation = GL_FUNC_ADD;

		// ��Ӱ
		bool ShadowCast = true;
		bool ShadowReceive = true;
	};
}


