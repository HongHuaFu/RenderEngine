#ifndef ENGINE_MACROS_HPP
#define ENGINE_MACROS_HPP

#include "../Core/Log.hpp"
#include <memory>
#include <functional>

#define BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef APPLICATION_
	// Client log macros
	#define TRACE(...)	 ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define INFO(...)	 ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
	#define WARN(...)	 ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define ERROR(...)	 ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#else
	// Engine log macros
	#define TRACE(...)   ::Engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define INFO(...)    ::Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define WARN(...)    ::Engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define ERROR(...)   ::Engine::Log::GetEngineLogger()->error(__VA_ARGS__)
#endif

#endif
