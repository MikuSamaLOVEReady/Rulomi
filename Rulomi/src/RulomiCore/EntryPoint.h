#pragma once

#ifdef  RLM_PLATFORM_WINDOWS
//����һ���ⲿ�ĺ�������compiler���ⲿѰ����������Ķ���
extern Rulomi::Application* Rulomi::CreateApplication();

int main(int argc, char** argv) {
	printf("Love Miku\n");
	Rulomi::Application* app = Rulomi::CreateApplication();
	app->Run();
	delete app;

}

#endif // 
