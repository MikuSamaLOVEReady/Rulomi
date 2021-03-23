#pragma once

#include "RulomiPch.h"
#include "RulomiCore/Core.h"
#include "RulomiCore/Events/Event.h"


namespace Rulomi {

	//根据不同的平台创建不同类型的窗口 窗体的属性 
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		//struct 也可被当成一个 class 默认初始化
	   // 默认窗体大小
		WindowProps(const std::string& title = "Rulomi Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			:Title(title), Width(width), Height(height)
		{}
   };


	///
	///**************Window Interface**************
	///
	// 不同平台实现规则不同
	class RULOMI_API Window {
	public:
		//  只能让这个函数指针 指向 返回类型为void 并且参数是（Event&引用）的函数
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};
		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window attributes
		//设置窗口事件处理函数
		virtual void SetEventCallback(const  std::function<void(Event&)>& callback) = 0;
         //这是干啥？
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;
		//返回当前窗口（为何 不一定只是 GLFW window 还有可能是别的类型）处于扩展性考虑
		virtual void* GetNativeWindow() const= 0;

		//  传递的参数是窗口具体属性  不同平台只用实现这个函数就可
		// 但是为啥是 static的呢？
		// WindowProps 存在一个默认 constu
		static Window* Create(const WindowProps& props = WindowProps());

	};





}