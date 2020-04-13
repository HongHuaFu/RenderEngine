#include "Material.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "TextureCube.hpp"


namespace RE
{
	Material::Material()
	{

	}

	Material::Material(Shader* shader)
	{
		m_Shader = shader;
	}


	Shader* Material::GetShader()
	{
		return m_Shader;
	}

	void Material::SetShader(Shader* shader)
	{
		m_Shader = shader;
	}

	Material Material::Copy()
	{
		Material copy(m_Shader);

		copy.Type = Type;
		copy.Color = Color;
		copy.DepthTest = DepthTest;
		copy.DepthWrite = DepthWrite;
		copy.DepthCompare = DepthCompare;
		copy.Cull = Cull;
		copy.CullFace = CullFace;
		copy.CullWindingOrder = CullWindingOrder;
		copy.Blend = Blend;
		copy.BlendSrc = BlendSrc;
		copy.BlendDst = BlendDst;
		copy.BlendEquation = BlendEquation;
		copy.m_Uniforms = m_Uniforms;
		copy.m_SamplerUniforms = m_SamplerUniforms;

		return copy;
	}


	void Material::SetBool(std::string name, bool value)
	{
		m_Uniforms[name].Type = Shader_Type::BOOL;
		m_Uniforms[name].Bool = value;
	}


	void Material::SetInt(std::string name, int value)
	{
		m_Uniforms[name].Type = Shader_Type::INT;
		m_Uniforms[name].Int  = value;
	}


	void Material::SetFloat(std::string name, float value)
	{
		m_Uniforms[name].Type  = Shader_Type::FLOAT;
		m_Uniforms[name].Float = value;
	}


	void Material::SetTexture(std::string name, Texture* value, unsigned int unit)
	{
		m_SamplerUniforms[name].Unit = unit;
		m_SamplerUniforms[name].Texture = value;

		switch (value->m_Target)
		{
		case GL_TEXTURE_1D:
			m_SamplerUniforms[name].Type = Shader_Type::SAMPLER1D;
			break;
		case GL_TEXTURE_2D:
			m_SamplerUniforms[name].Type = Shader_Type::SAMPLER2D;
			break;
		case GL_TEXTURE_3D:
			m_SamplerUniforms[name].Type = Shader_Type::SAMPLER3D;
			break;
		case GL_TEXTURE_CUBE_MAP:
			m_SamplerUniforms[name].Type = Shader_Type::SAMPLERCUBE;
			break;
		}

		// 采样器设置需要额外设定贴图插槽步骤
		if (m_Shader)
		{
			m_Shader->Use();
			m_Shader->SetInt(name, unit);
		}
	}

	void Material::SetTextureCube(std::string name, TextureCube* value, unsigned int unit)
	{
		m_SamplerUniforms[name].Unit = unit;
		m_SamplerUniforms[name].Type = Shader_Type::SAMPLERCUBE;
		m_SamplerUniforms[name].TextureCube = value;

		// 采样器设置需要额外设定贴图插槽步骤
		if (m_Shader)
		{
			m_Shader->Use();
			m_Shader->SetInt(name, unit);
		}
	}


	void Material::SetVector(std::string name, glm::vec2 value)
	{
		m_Uniforms[name].Type = Shader_Type::VEC2;
		m_Uniforms[name].Vec2 = value;
	}

	void Material::SetVector(std::string name, glm::vec3 value)
	{
		m_Uniforms[name].Type = Shader_Type::VEC3;
		m_Uniforms[name].Vec3 = value;
	}

	void Material::SetVector(std::string name, glm::vec4 value)
	{
		m_Uniforms[name].Type = Shader_Type::VEC4;
		m_Uniforms[name].Vec4 = value;
	}

	void Material::SetMatrix(std::string name, glm::mat2 value)
	{
		m_Uniforms[name].Type = Shader_Type::MAT2;
		m_Uniforms[name].Mat2 = value;
	}


	void Material::SetMatrix(std::string name, glm::mat3 value)
	{
		m_Uniforms[name].Type = Shader_Type::MAT3;
		m_Uniforms[name].Mat3 = value;
	}

	void Material::SetMatrix(std::string name, glm::mat4 value)
	{
		m_Uniforms[name].Type = Shader_Type::MAT4;
		m_Uniforms[name].Mat4 = value;
	}

	std::map<std::string, UniformValue>* Material::GetUniforms()
	{
		return &m_Uniforms;
	}

	std::map<std::string, UniformValueSampler>* Material::GetSamplerUniforms()
	{
		return &m_SamplerUniforms;
	}
}


