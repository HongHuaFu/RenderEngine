#pragma once

#include "Log.hpp"

#include <memory>
#include <functional>


#ifdef EDITOR_
// Client log macros
#define LOG_TRACE(...)	 ::RE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	 ::RE::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	 ::RE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	 ::RE::Log::GetClientLogger()->error(__VA_ARGS__)
#else
// Engine log macros
#define LOG_TRACE(...)   ::RE::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)    ::RE::Log::GetEngineLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)    ::RE::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)   ::RE::Log::GetEngineLogger()->error(__VA_ARGS__)
#endif

#ifndef UNABLE_ASSERTS
#define LOG_ASSERT(x, ...) { if(!(x)) { ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define LOG_ASSERT(x, ...)
#endif

#define BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// 获取当前字符串的哈希值
#define SID(string) custom_simple_hash(string)

inline unsigned int custom_simple_hash(const std::string& str)
{
	unsigned int hash = 0;

	for (auto& it : str) 
	{
		hash = 37 * hash + 17 * static_cast<char>(it);
	}

	return hash;
}

inline unsigned int custom_simple_hash(const char* cStr)
{
	std::string str(cStr);
	return custom_simple_hash(str);
}


