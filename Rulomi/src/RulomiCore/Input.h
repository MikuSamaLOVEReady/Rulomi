#pragma once

#include "Core.h"

namespace Rulomi {
	
	//����class���� ÿ����ͬ���ڵ�������ѯ 
	// ʵ��ͬʱ���� Alt �� ��������ʱ�� engine �������ķ�Ӧ
	class Input
	{
	public:
		//��ѯ����
		 static bool IsKeyPressed(int keycode);
		//��ѯ���
		 static bool IsMouseButtonPressed(int button);
		 static float GetMouseX();
		 static float GetMouseY();
		 static std::pair<float, float> GetMousePosition();
	};


}