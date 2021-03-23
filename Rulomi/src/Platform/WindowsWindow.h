#pragma once

#include "RulomiCore/Window.h"
#include "Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>


///
/// windows �����µĴ�������
///

namespace Rulomi {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const  override { return m_Data.Width; };
		inline unsigned int GetHeight() const  override { return m_Data.Height; };


		//window attributes 
		//SetEventCallback �������
		inline void SetEventCallback(const  std::function<void(Event&)>& callback) override { m_Data.EventCallback = callback; };
		//���Ǹ�ɶ��
		void SetVSync(bool enable) override ;
		bool IsVSync() const override;
		//���ݲ�ͬ��ƽ̨��ȡ��Ӧƽ̨��window
		inline virtual void* GetNativeWindow() const { return m_Window; };

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		// engine ��ֹһ��window but Ŀǰ�����һ��
		GLFWwindow* m_Window;
		//�ݶ�ÿ��window ֻ��һ�� context
		GraphicsContext*  m_Context;


		struct  WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};



}








