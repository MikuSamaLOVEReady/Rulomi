#pragma once

#ifdef  RLM_PLATFORM_WINDOWS
//申明一个外部的函数，让compiler在外部寻找这个函数的定义
extern Rulomi::Application* Rulomi::CreateApplication();


//只修改head file 为啥不用重写生成dll？
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
