#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

#include "RulomiCore/ImGui/ImGuiLayer.h"



namespace Rulomi {

	//application 引擎主体只能是一个单件siglten
	class  RULOMI_API Application
	{
	public: 
		Application();
		//C++的base类为啥都需要被设置成virtual？
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		//获取当前引擎的单例 obj
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		//这个unique window是指向当前选中 window的指针  但整个window 可能不是由GLFW实现的可能混杂别的类型
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;

		

	};

	// 这个函数需要在client端 也就是游戏端实现。 只是在引擎中申明
	Application* CreateApplication();


}




