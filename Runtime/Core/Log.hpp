#pragma once

#include <memory.h>
#include <spdlog/spdlog.h>

namespace RE
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() 
		{
			return s_EngineLogger; 
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() 
		{ 
			return s_ClientLogger; 
		}

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}



