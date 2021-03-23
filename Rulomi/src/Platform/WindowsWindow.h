#pragma once

#include "RulomiCore/Window.h"
#include "Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>


///
/// windows 环境下的窗口设置
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
		//SetEventCallback 这个是让
		inline void SetEventCallback(const  std::function<void(Event&)>& callback) override { m_Data.EventCallback = callback; };
		//这是干啥？
		void SetVSync(bool enable) override ;
		bool IsVSync() const override;
		//根据不同的平台获取对应平台的window
		inline virtual void* GetNativeWindow() const { return m_Window; };

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		// engine 不止一个window but 目前就这个一个
		GLFWwindow* m_Window;
		//暂定每个window 只有一个 context
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








