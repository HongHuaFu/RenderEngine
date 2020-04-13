#include "LoadShader.hpp"
#include "../Core/Macro.hpp"
#include "../Render/Shader.hpp"

#include <fstream>

namespace RE
{
	// ��ȡshader�ַ�
	static std::string ReadShader(std::ifstream& file, const std::string& name, std::string path)
	{
		// ��ɫ���ļ������ļ���·��
		std::string directory = path.substr(0, path.find_last_of("/\\"));
		std::string source, line;
		while (std::getline(file, line))
		{
			// ��չ"#include ./path.glsl"����
			if (line.substr(0, 8) == "#include")
			{
				std::string includePath = directory + "/" + line.substr(9);
				std::ifstream includeFile(includePath);
				if (includeFile.is_open())
				{
					// ����#include��glsl�ļ��ַ�ȫ�����ƹ���
					// ��������
					// ��#include��glsl�ļ�#include����glsl
					source += ReadShader(includeFile, name, includePath);
				}
				else
				{
					LOG_ERROR("Shader: {0}: include: {1} failed to open.",name,includePath);
				}
				includeFile.close();
			}
			else
				source += line + "\n";
		}
		return source;
	}

	// vs+fs����ɫ�����
	Shader LoadShader::Load(std::string name,std::string vsPath,std::string fsPath,std::vector<std::string> defines)
	{
		std::ifstream vsFile, fsFile;
		vsFile.open(vsPath);
		fsFile.open(fsPath);

		if (!vsFile.is_open() || !fsFile.is_open())
		{
			LOG_ERROR("Shader failed to load at path: {0} and {1}.",vsPath,fsPath);
			return Shader();
		}

		std::string vsSource = ReadShader(vsFile, name, vsPath);
		std::string fsSource = ReadShader(fsFile, name, fsPath);

		Shader shader(name, vsSource, fsSource, defines);

		vsFile.close();
		fsFile.close();

		return shader;
	}
}
