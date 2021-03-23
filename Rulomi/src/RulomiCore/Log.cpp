#include"RulomiPch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Rulomi {

	//static 智能指针的定义
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		//设置 输出 格式
		spdlog::set_pattern("%^[%T] %n: %v%$");
		// create color multi threaded logger（这里的参数相当于给logger 给名）
		s_CoreLogger = spdlog::stdout_color_mt("Rulomi");
		//设置显示等级？ trace是最低级/
	   // spdlog::set_level(spdlog::level::debug); 
	    // Set global log level to debug  如果直接调用库里的函数设置 
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("Game");
		s_ClientLogger->set_level(spdlog::level::trace);

	}



}