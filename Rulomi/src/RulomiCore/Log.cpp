#include"RulomiPch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Rulomi {

	//static ����ָ��Ķ���
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		//���� ��� ��ʽ
		spdlog::set_pattern("%^[%T] %n: %v%$");
		// create color multi threaded logger������Ĳ����൱�ڸ�logger ������
		s_CoreLogger = spdlog::stdout_color_mt("Rulomi");
		//������ʾ�ȼ��� trace����ͼ�/
	   // spdlog::set_level(spdlog::level::debug); 
	    // Set global log level to debug  ���ֱ�ӵ��ÿ���ĺ������� 
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("Game");
		s_ClientLogger->set_level(spdlog::level::trace);

	}



}