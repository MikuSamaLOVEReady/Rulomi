#pragma once


namespace Rulomi
{
	//Most genaric
	// 各个平台renderer都继承于此
	class GraphicsContext
	{
	public:
	 virtual	void Init() = 0;
	 virtual void SwapBuffers() = 0;


	};


}