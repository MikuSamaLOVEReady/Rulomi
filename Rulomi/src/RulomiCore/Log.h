#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
//spdlog/fmt/ostr.h  ������ô��������ǵ�log �ܹ���ӡ�����Լ�event�¼���
// ��ô�����ģ� ����wiki
// ����Ǽ��� spdlog �� operator ����
#include "spdlog/fmt/ostr.h"





namespace Rulomi {

	class RULOMI_API Log
	{
	public:

		//��̬����~ �����־ϵͳ�ĳ�ʼ��
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		//��ֻ�������� ������̬���� ����ô��������ʲôʱ�����أ���
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

//Core log �ɱ������
#define RLM_CORE_TRACE(...)		 ::Rulomi::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RLM_CORE_DEBUG(...)	 ::Rulomi::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define RLM_CORE_INFO(...)		 ::Rulomi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RLM_CORE_WARN(...)	 ::Rulomi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RLM_CORE_ERROR(...)	 ::Rulomi::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RLM_CORE_FATAL(...)		 ::Rulomi::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define RLM_CORE_OFF(...)			 ::Rulomi::Log::GetCoreLogger()->off(__VA_ARGS__)

//Client log ��
#define RLM_Client_TRACE(...)		 ::Rulomi::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RLM_Client_DEBUG(...)	 ::Rulomi::Log::GetClientLogger()->debug(__VA_ARGS__)
#define RLM_Client_INFO(...)		 ::Rulomi::Log::GetClientLogger()->info(__VA_ARGS__)
#define RLM_Client_WARN(...)	 ::Rulomi::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RLM_Client_ERROR(...)	 ::Rulomi::Log::GetClientLogger()->error(__VA_ARGS__)
#define RLM_Client_FATAL(...)		 ::Rulomi::Log::GetClientLogger()->critical(__VA_ARGS__)
#define RLM_Client_OFF(...)			 ::Rulomi::Log::GetClientLogger()->off(__VA_ARGS__)





