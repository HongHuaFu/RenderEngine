#pragma once

// 材质系统
// 存储Uniform和采样器的值
// 每一个SceneNode都会至少包含一个材质，提交到渲染命令的时候
// 将会遍历材质的Uniform/采样器数组
// 并修改对应的Shader插槽

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
		DEFAULT, // 当前管线下的默认材质
		CUSTOM,  // 当前管线下的自定义材质
		POST_PROCESS, // 后处理材质
	};

	class Material
	{
	public:
		Material();
		Material(Shader* shader);

		Shader* GetShader();
		void SetShader(Shader* shader);

		Material Copy();

		// 设置的时候，把uniform类型更改为正确的值
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

		// 在设置材质值的时候填充散列表
		// 没有设置值就不会写入表中

		// 仅当当前材质进入渲染队列时渲染，才会更新m_Uniforms、m_SamplerUniforms的值到Shader中
		std::map<std::string, UniformValue> m_Uniforms;
		std::map<std::string, UniformValueSampler> m_SamplerUniforms; 

	public:
		// 默认材质类型设置为自定义
		MaterialType Type = MaterialType::CUSTOM;
		glm::vec4 Color = glm::vec4(1.0f);

		// 深度
		bool DepthTest = true;
		bool DepthWrite = true;

		unsigned int DepthCompare = GL_LESS;

		// 面剔除
		bool Cull = true;
		unsigned int CullFace = GL_BACK;
		unsigned int CullWindingOrder = GL_CCW;

		// 混合
		bool Blend = false;
		unsigned int BlendSrc = GL_ONE; 
		unsigned int BlendDst = GL_ONE_MINUS_SRC_ALPHA;
		unsigned int BlendEquation = GL_FUNC_ADD;

		// 阴影
		bool ShadowCast = true;
		bool ShadowReceive = true;
	};
}


