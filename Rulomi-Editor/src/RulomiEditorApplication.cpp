#include "Rulomi.h"
#include "RulomiCore/EntryPoint.h"

#include "EditorLayer.h"

namespace Rulomi {
	class RulomiEditorApplication :public Application
	{
	public:
		RulomiEditorApplication()
			:Application("RulomiEditor")
		{
			PushLayer(new EditorLayer());
		}
		~RulomiEditorApplication()
		{

		}



	};

	//引擎内部的函数的申明 由游戏对象定义
	Application* CreateApplication()
	{
		return new RulomiEditorApplication();
	}

}
