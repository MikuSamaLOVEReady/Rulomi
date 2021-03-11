#pragma once

#ifdef  RLM_PLATFORM_WINDOWS
//申明一个外部的函数，让compiler在外部寻找这个函数的定义
extern Rulomi::Application* Rulomi::CreateApplication();

int main(int argc, char** argv) {
	printf("Love Miku\n");
	Rulomi::Application* app = Rulomi::CreateApplication();
	app->Run();
	delete app;

}

#endif // 
