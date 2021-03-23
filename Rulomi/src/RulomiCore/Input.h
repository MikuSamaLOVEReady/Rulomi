#pragma once

#include "Core.h"

namespace Rulomi {
	
	//单例class用于 每个不同窗口的输入轮询
	// 实现同时按下 Alt 和 鼠标左键的时候 engine 有怎样的反应
	class RULOMI_API Input
	{
	public:
		//轮询键盘
		inline static bool IsKeyPressed(int keycode) { return  s_Instance->IsKeyPressedImpl(keycode); }
		//轮询鼠标
		inline static bool IsMouseButtonPressed(int button) { return  s_Instance->IsMouseButtonPressedImpliment(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpliment(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpliment(); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpliment(); }

	
		//跨平台接口 由平台自身单独实现
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpliment(int button) = 0;
		virtual float GetMouseXImpliment() = 0;
		virtual float GetMouseYImpliment() = 0;
		virtual std::pair<float, float> GetMousePositionImpliment() = 0;



	private:
		// 类内的static 仅仅只是申明
		// 而其他普通成员就是定义
		static Input* s_Instance;
		// 静态成员 类内只是声明而无定义。这样conpiler不会为他们分配空间，自然就找不到定义
		//static Input* s_Ins;
		//static int a;



	};


}