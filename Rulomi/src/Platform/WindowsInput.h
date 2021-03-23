#pragma once
#include "RulomiCore/Core.h"
#include "RulomiCore/Input.h"


namespace Rulomi {

	class   WindowsInput : public Input
	{



	protected:
		//keep virtual. 只是表达这个函数是重写的虚函数
		virtual  bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpliment(int button) override;
		virtual float GetMouseXImpliment() override;
		virtual float GetMouseYImpliment() override;
		virtual  std::pair<float, float>  GetMousePositionImpliment() override;

	};



}

