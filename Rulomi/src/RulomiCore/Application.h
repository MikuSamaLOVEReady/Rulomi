#pragma once
#include "Core.h"

namespace Rulomi {

	class  RULOMI_API Application
	{
	public: 
		Application();
		//C++��base��Ϊɶ����Ҫ�����ó�virtual��
		virtual ~Application();

		void Run();
	};

	// ���������Ҫ��client�� Ҳ������Ϸ��ʵ�֡� ֻ��������������
	Application* CreateApplication();


}




