#include "LoadShader.hpp"
#include <fstream>

namespace Engine::Loader
{
	Shader LoadShader(std::string name,
					  std::string vsPath,
					  std::string fsPath,
					  std::vector<std::string> defines)
	{
		std::ifstream vsFile, fsFile;
		vsFile.open(vsPath);
		fsFile.open(fsPath);
	}

}
