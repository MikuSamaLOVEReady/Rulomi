#pragma once

#include "Core.h"

namespace Rulomi {
	
	//����class���� ÿ����ͬ���ڵ�������ѯ
	// ʵ��ͬʱ���� Alt �� ��������ʱ�� engine �������ķ�Ӧ
	class RULOMI_API Input
	{
	public:
		//��ѯ����
		inline static bool IsKeyPressed(int keycode) { return  s_Instance->IsKeyPressedImpl(keycode); }
		//��ѯ���
		inline static bool IsMouseButtonPressed(int button) { return  s_Instance->IsMouseButtonPressedImpliment(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpliment(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpliment(); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpliment(); }

	
		//��ƽ̨�ӿ� ��ƽ̨������ʵ��
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpliment(int button) = 0;
		virtual float GetMouseXImpliment() = 0;
		virtual float GetMouseYImpliment() = 0;
		virtual std::pair<float, float> GetMousePositionImpliment() = 0;



	private:
		// ���ڵ�static ����ֻ������
		// ��������ͨ��Ա���Ƕ���
		static Input* s_Instance;
		// ��̬��Ա ����ֻ���������޶��塣����conpiler����Ϊ���Ƿ���ռ䣬��Ȼ���Ҳ�������
		//static Input* s_Ins;
		//static int a;



	};


}