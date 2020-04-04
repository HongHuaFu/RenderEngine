#include "Shader.hpp"
#include "../Core/Macro.hpp"
#include <glad/glad.h>

namespace Engine
{
	Shader::Shader(std::string name,
		std::string vsCode,
		std::string fsCode,
		std::vector<std::string> defines)
	{
		m_Name = name;

		// ����vs��fs
		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

		m_ID = glCreateProgram();

		int status;
		char log[1024];

		// ��ɫ�����������
		if (defines.size() > 0)
		{
			std::vector<std::string> vsMergedCode;
			std::vector<std::string> fsMergedCode;

			// ȷ��glsl���д����Ƿ��ṩ�� "#version"
			// ���ṩ����ѵ�һ����ȡ���������û������defines�������ٰ�#version�������
			// glsl ���������� #version,���ͻ�Ĭ�ϰ汾Ϊ1.1
			std::string firstLine = vsCode.substr(0, vsCode.find("\n"));
			if (firstLine.find("#version") != std::string::npos)
			{
				// ��ӵ�һ�е���ɫ�������ַ����б���ɾ����һ�е���ɫ�����롣
				vsCode = vsCode.substr(vsCode.find("\n") + 1, vsCode.length() - 1);
				vsMergedCode.push_back(firstLine + "\n");
			}

			// ͬ����ƬԪ��ɫ������ͬ����
			firstLine = fsCode.substr(0, fsCode.find("\n"));
			if (firstLine.find("#version") != std::string::npos)
			{
				fsCode = fsCode.substr(fsCode.find("\n") + 1, fsCode.length() - 1);
				fsMergedCode.push_back(firstLine + "\n");
			}

			// ��Ӷ�������
			for (unsigned int i = 0; i < defines.size(); ++i)
			{
				std::string define = "#define " + defines[i] + "\n";
				vsMergedCode.push_back(define);
				fsMergedCode.push_back(define);
			}

			// �ϲ�
			vsMergedCode.push_back(vsCode);
			fsMergedCode.push_back(fsCode);

			// C�ַ������ڴ�����
			const char **vsStringsC = new const char*[vsMergedCode.size()];
			const char **fsStringsC = new const char*[fsMergedCode.size()];

			for (unsigned int i = 0; i < vsMergedCode.size(); ++i)
				vsStringsC[i] = vsMergedCode[i].c_str();
			for (unsigned int i = 0; i < fsMergedCode.size(); ++i)
				fsStringsC[i] = fsMergedCode[i].c_str();

			glShaderSource(vs, vsMergedCode.size(), vsStringsC, NULL);
			glShaderSource(fs, fsMergedCode.size(), fsStringsC, NULL);
			delete[] vsStringsC;
			delete[] fsStringsC;
		}
		else
		{
			const char *vsSourceC = vsCode.c_str();
			const char *fsSourceC = fsCode.c_str();
			glShaderSource(vs, 1, &vsSourceC, NULL);
			glShaderSource(fs, 1, &fsSourceC, NULL);
		}
		glCompileShader(vs);
		glCompileShader(fs);

		glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			glGetShaderInfoLog(vs, 1024, NULL, log);
			LOG_ERROR("Vertex shader compilation error at: {0}!\n",name);
			LOG_ERROR("ERROR Detail: {0}",std::string(log));
		}
		glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			glGetShaderInfoLog(fs, 1024, NULL, log);

			LOG_ERROR("Fragment shader compilation error at: {0}!\n",name);
			LOG_ERROR("ERROR Detail: {0}",std::string(log));
		}

		glAttachShader(m_ID, vs);
		glAttachShader(m_ID, fs);
		glLinkProgram(m_ID);

		glGetProgramiv(m_ID, GL_LINK_STATUS, &status);
		if (!status)
		{
			glGetProgramInfoLog(m_ID, 1024, NULL, log);
			LOG_ERROR("Shader program linking error: {0}",std::string(log));
		}

		glDeleteShader(vs);
		glDeleteShader(fs);

		// ��������/Uniform����
		int nrAttributes, nrUniforms;
		glGetProgramiv(m_ID, GL_ACTIVE_ATTRIBUTES, &nrAttributes);
		glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &nrUniforms);
		
		Attributes.resize(nrAttributes);
		Uniforms.resize(nrUniforms);

		char buffer[128];
		for (unsigned int i = 0; i < nrAttributes; ++i)
		{
			GLenum glType;
			glGetActiveAttrib(m_ID, i, sizeof(buffer), 0, &Attributes[i].Size, &glType, buffer);
			Attributes[i].Name = std::string(buffer);

			// TODO: ������ȷ������
			Attributes[i].Type = SHADER_TYPE_BOOL; 

			Attributes[i].Location = glGetAttribLocation(m_ID, buffer);
		}


		for (unsigned int i = 0; i < nrUniforms; ++i)
		{
			GLenum glType;
			glGetActiveUniform(m_ID, i, sizeof(buffer), 0, &Uniforms[i].Size, &glType, buffer);
			Uniforms[i].Name = std::string(buffer);

			// TODO: ������ȷ������
			Uniforms[i].Type = SHADER_TYPE_BOOL;  

			Uniforms[i].Location = glGetUniformLocation(m_ID, buffer);
		}

		
	}

	inline void Shader::Use()
	{
		glUseProgram(m_ID);
	}

	bool Shader::HasUniform(std::string name)
	{
		for (unsigned int i = 0; i < Uniforms.size(); ++i)
		{
			if(Uniforms[i].Name == name)
				return true;
		}

		return false;
	}

	void Shader::SetInt(std::string location,int value)
	{
		int loc = GetUniformLocation(location);
		if (loc >= 0)
			glUniform1i(loc, value);
	}

	void Shader::SetBool(std::string location, bool value)
	{
		int loc = GetUniformLocation(location);
		if (loc >= 0)
			glUniform1i(loc, (int)value);
	}


	void Shader::SetFloat(std::string location, float value)
	{
		int loc = GetUniformLocation(location);
		if (loc >= 0)
			glUniform1f(loc, value);
	}

	void Shader::SetVector(std::string location, glm::vec2 value)
	{
		int loc = GetUniformLocation(location);
		if (loc >= 0)
			glUniform2fv(loc, 1, &value[0]);        
	}

	void Shader::SetVector(std::string location, glm::vec3 value)
	{
		int loc = GetUniformLocation(location);
		if (loc >= 0)
			glUniform3fv(loc, 1, &value[0]);
	}

	void Shader::SetVector(std::string location, glm::vec4 value)
	{
		int loc = GetUniformLocation(location);
		if (loc >= 0)
			glUniform4fv(loc, 1, &value[0]);
	}

	void Shader::SetVectorArray(std::string location, int size, const std::vector<glm::vec2>& values)
	{
		unsigned int loc = glGetUniformLocation(m_ID, location.c_str());
		if (loc >= 0)
		{
			glUniform2fv(loc, size, (float*)(&values[0].x));
		}
	}

	void Shader::SetVectorArray(std::string location, int size, const std::vector<glm::vec3>& values)
	{
		unsigned int loc = glGetUniformLocation(m_ID, location.c_str());
		if (loc >= 0)
		{
			glUniform3fv(loc, size, (float*)(&values[0].x));
		}
	}

	void Shader::SetVectorArray(std::string location, int size, const std::vector<glm::vec4>& values)
	{
		unsigned int loc = glGetUniformLocation(m_ID, location.c_str());
		if (loc >= 0)
		{
			glUniform4fv(loc, size, (float*)(&values[0].x));
		}
	}

	void Shader::SetMatrix(std::string location, glm::mat2 value)
	{
		int loc = GetUniformLocation(location);
		if (loc >= 0)
			glUniformMatrix2fv(loc, 1, GL_FALSE, &value[0][0]);
	}

	void Shader::SetMatrix(std::string location, glm::mat3 value)
	{
		int loc = GetUniformLocation(location);
		if (loc >= 0)
			glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
	}

	void Shader::SetMatrix(std::string location, glm::mat4 value)
	{
		int loc = GetUniformLocation(location);
		if (loc >= 0)
			glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
	}

	

	int Shader::GetUniformLocation(std::string name)
	{
		for (unsigned int i = 0; i < Uniforms.size(); ++i)
		{
			if(Uniforms[i].Name == name)
				return Uniforms[i].Location;
		}
		return -1;
	}

}

