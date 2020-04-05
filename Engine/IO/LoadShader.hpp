#ifndef ENGINE_LOAD_SHADER_HPP
#define ENGINE_LOAD_SHADER_HPP


#include <string>
#include <vector>

namespace Engine
{
	class Shader;
	class LoadShader
	{
	public:
		static Shader Load(std::string name, 
						   std::string vsPath, 
						   std::string fsPath, 
						   std::vector<std::string> defines = std::vector<std::string>());

	};
	

		
}

#endif 
