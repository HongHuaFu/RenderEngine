#include "LoadShader.hpp"
#include "../Core/Macro.hpp"
#include "../Render/Shader.hpp"

#include <fstream>

namespace RE
{
	// 读取shader字符
	static std::string ReadShader(std::ifstream& file, const std::string& name, std::string path)
	{
		// 着色器文件所在文件夹路径
		std::string directory = path.substr(0, path.find_last_of("/\\"));
		std::string source, line;
		while (std::getline(file, line))
		{
			// 扩展"#include ./path.glsl"功能
			if (line.substr(0, 8) == "#include")
			{
				std::string includePath = directory + "/" + line.substr(9);
				std::ifstream includeFile(includePath);
				if (includeFile.is_open())
				{
					// 将被#include的glsl文件字符全部复制过来
					// 迭代复制
					// 被#include的glsl文件#include其它glsl
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

	// vs+fs的着色器组合
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
