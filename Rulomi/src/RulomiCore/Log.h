#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
//spdlog/fmt/ostr.h  这个包用处是让我们的log 能够打印我们自己event事件？
// 怎么做到的？ 看看wiki
// 这个是加载 spdlog 的 operator 《《
#include "spdlog/fmt/ostr.h"





namespace Rulomi {

	class RULOMI_API Log
	{
	public:

		//静态函数~ 存放日志系统的初始化
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		//这只是申明了 两个静态变量 （那么他俩的是什么时候定义呢？）
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

//Core log 可变参数宏
#define RLM_CORE_TRACE(...)		 ::Rulomi::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RLM_CORE_DEBUG(...)	 ::Rulomi::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define RLM_CORE_INFO(...)		 ::Rulomi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RLM_CORE_WARN(...)	 ::Rulomi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RLM_CORE_ERROR(...)	 ::Rulomi::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RLM_CORE_FATAL(...)		 ::Rulomi::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define RLM_CORE_OFF(...)			 ::Rulomi::Log::GetCoreLogger()->off(__VA_ARGS__)

//Client log 宏
#define RLM_Client_TRACE(...)		 ::Rulomi::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RLM_Client_DEBUG(...)	 ::Rulomi::Log::GetClientLogger()->debug(__VA_ARGS__)
#define RLM_Client_INFO(...)		 ::Rulomi::Log::GetClientLogger()->info(__VA_ARGS__)
#define RLM_Client_WARN(...)	 ::Rulomi::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RLM_Client_ERROR(...)	 ::Rulomi::Log::GetClientLogger()->error(__VA_ARGS__)
#define RLM_Client_FATAL(...)		 ::Rulomi::Log::GetClientLogger()->critical(__VA_ARGS__)
#define RLM_Client_OFF(...)			 ::Rulomi::Log::GetClientLogger()->off(__VA_ARGS__)





