#pragma once

#include <string>
#include <vector>

namespace RE
{
	class Shader;
	class LoadShader
	{
	public:
		static Shader Load(std::string, std::string, std::string,std::vector<std::string> defines = std::vector<std::string>());
	};
}

