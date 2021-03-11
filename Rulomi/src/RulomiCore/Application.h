#pragma once
#include "Core.h"

namespace Rulomi {

	class  RULOMI_API Application
	{
	public: 
		Application();
		//C++的base类为啥都需要被设置成virtual？
		virtual ~Application();

		void Run();
	};

	// 这个函数需要在client端 也就是游戏端实现。 只是在引擎中申明
	Application* CreateApplication();


}




