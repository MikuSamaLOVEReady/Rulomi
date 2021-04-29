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

	//�����ڲ��ĺ��������� ����Ϸ������
	Application* CreateApplication()
	{
		return new RulomiEditorApplication();
	}

}
