#pragma once

#include "RulomiPch.h"
#include "RulomiCore/Core.h"
#include "RulomiCore/Events/Event.h"


namespace Rulomi {

	//���ݲ�ͬ��ƽ̨������ͬ���͵Ĵ��� ��������� 
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		//struct Ҳ�ɱ�����һ�� class Ĭ�ϳ�ʼ��
	   // Ĭ�ϴ����С
		WindowProps(const std::string& title = "Rulomi Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			:Title(title), Width(width), Height(height)
		{}
   };


	///
	///**************Window Interface**************
	///
	// ��ͬƽ̨ʵ�ֹ���ͬ
	class RULOMI_API Window {
	public:
		//  ֻ�����������ָ�� ָ�� ��������Ϊvoid ���Ҳ����ǣ�Event&���ã��ĺ���
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window attributes
		//���ô����¼�������
		virtual void SetEventCallback(const  std::function<void(Event&)>& callback) = 0;
         //���Ǹ�ɶ��
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;
		//���ص�ǰ���ڣ�Ϊ�� ��һ��ֻ�� GLFW window ���п����Ǳ�����ͣ�������չ�Կ���
		virtual void* GetNativeWindow() const= 0;

		//  ���ݵĲ����Ǵ��ھ�������  ��ͬƽֻ̨��ʵ����������Ϳ�
		// ����Ϊɶ�� static���أ�
		// WindowProps ����һ��Ĭ�� constu
		static Window* Create(const WindowProps& props = WindowProps());

	};





}