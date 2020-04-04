#ifndef ENGINE_LOAD_SHADER_HPP
#define ENGINE_LOAD_SHADER_HPP

#include "../Shading/Shader.hpp"
#include <string>
#include <vector>

namespace Engine::Loader
{
	static Shader LoadShader(std::string name, 
							 std::string vsPath, 
							 std::string fsPath, 
							 std::vector<std::string> defines = std::vector<std::string>());
		
}

#endif 
