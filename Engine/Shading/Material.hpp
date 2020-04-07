#ifndef ENGINE_MATERIAL_HPP
#define ENGINE_MATERIAL_HPP

#include "ShaderType.hpp"

#include <map>
#include <string>
#include <glm/glm.hpp>

// TODO: 使用自定义类型代替
#include <glad/glad.h>

namespace Engine
{
	class Shader;

	enum MaterialType
	{
		MATERIAL_DEFAULT,
		MATERIAL_CUSTOM,
		MATERIAL_POST_PROCESS,
	};

	class Material
	{
	public:
		Material();
		Material(Shader* shader);

		Shader* GetShader();
		void SetShader(Shader* shader);

		Material Copy();

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
		// TODO: 使用share_ptr代替
		Shader* m_Shader; 

		std::map<std::string, UniformValue> m_Uniforms;
		std::map<std::string, UniformValueSampler> m_SamplerUniforms; //采样器

	public:
		MaterialType Type = MATERIAL_CUSTOM;
		glm::vec4 Color = glm::vec4(1.0f);

		// 深度
		bool   DepthTest    = true;
		bool   DepthWrite   = true;
		// TODO: 使用自定义类型代替 
		unsigned int DepthCompare = GL_LESS;

		// 面剔除
		bool Cull  = true;
		unsigned int CullFace         = GL_BACK;
		unsigned int CullWindingOrder = GL_CCW;

		// 混合
		bool Blend  = false;
		unsigned int BlendSrc      = GL_ONE; 
		unsigned int BlendDst      = GL_ONE_MINUS_SRC_ALPHA;
		unsigned int BlendEquation = GL_FUNC_ADD;

		// 阴影
		bool ShadowCast    = true;
		bool ShadowReceive = true;
	};
}

#endif // !ENGINE_MATERIAL_HPP
