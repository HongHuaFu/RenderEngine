#ifndef ENGINE_MACROS_HPP
#define ENGINE_MACROS_HPP

#include "../Core/Log.hpp"
#include <memory>
#include <functional>

#define BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef APPLICATION_
	// Client log macros
	#define LOG_TRACE(...)	 ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define LOG_INFO(...)	 ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
	#define LOG_WARN(...)	 ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define LOG_ERROR(...)	 ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#else
	// Engine log macros
	#define LOG_TRACE(...)   ::Engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define LOG_INFO(...)    ::Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define LOG_WARN(...)    ::Engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define LOG_ERROR(...)   ::Engine::Log::GetEngineLogger()->error(__VA_ARGS__)
#endif

#ifndef UNABLE_ASSERTS
#define LOG_ASSERT(x, ...) { if(!(x)) { ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define LOG_ASSERT(x, ...)
#endif


#endif
