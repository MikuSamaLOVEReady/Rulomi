#include <Rulomi.h>


class Sandbox : public Rulomi::Application {

public:
	Sandbox() {

	}

	~Sandbox() {

	}

};

//引擎内部的函数的申明 由游戏对象定义
Rulomi::Application* Rulomi::CreateApplication()
{
	return new Sandbox();
}


