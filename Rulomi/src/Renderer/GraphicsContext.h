#pragma once


namespace Rulomi
{
	//Most genaric
	// ����ƽ̨renderer���̳��ڴ�
	class GraphicsContext
	{
	public:
	 virtual	void Init() = 0;
	 virtual void SwapBuffers() = 0;


	};


}