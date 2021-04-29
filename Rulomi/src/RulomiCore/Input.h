#pragma once

#include "Core.h"

namespace Rulomi {
	
	//单例class用于 每个不同窗口的输入轮询 
	// 实现同时按下 Alt 和 鼠标左键的时候 engine 有怎样的反应
	class Input
	{
	public:
		//轮询键盘
		 static bool IsKeyPressed(int keycode);
		//轮询鼠标
		 static bool IsMouseButtonPressed(int button);
		 static float GetMouseX();
		 static float GetMouseY();
		 static std::pair<float, float> GetMousePosition();
	};


}