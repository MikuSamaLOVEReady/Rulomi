#include <Rulomi.h>


class Sandbox : public Rulomi::Application {

public:
	Sandbox() {

	}

	~Sandbox() {

	}

};

//�����ڲ��ĺ��������� ����Ϸ������
Rulomi::Application* Rulomi::CreateApplication()
{
	return new Sandbox();
}


