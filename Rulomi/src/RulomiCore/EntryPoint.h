#pragma once

#ifdef  RLM_PLATFORM_WINDOWS
//����һ���ⲿ�ĺ�������compiler���ⲿѰ����������Ķ���
extern Rulomi::Application* Rulomi::CreateApplication();


//ֻ�޸�head file Ϊɶ������д����dll��
int main(int argc, char** argv) {

	//Log system init
	Rulomi::Log::Init();
	RLM_CORE_TRACE("ENGINE Trace");
	RLM_CORE_WARN("ENGINE WARN ");
	RLM_Client_ERROR("CLient error");
	int a = 520;
	RLM_Client_INFO("MikuSama {0} ", a);

	//printf("Love Miku\n");
	Rulomi::Application* app = Rulomi::CreateApplication();
	app->Run();
	delete app;

}

#endif // 
