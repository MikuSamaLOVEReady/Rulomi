#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

#include "RulomiCore/ImGui/ImGuiLayer.h"



namespace Rulomi {

	//application ��������ֻ����һ������siglten
	class  RULOMI_API Application
	{
	public: 
		//����default ����
		Application(const std::string& name = "Rulomi Engine");
		//C++��base��Ϊɶ����Ҫ�����ó�virtual��
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		void ShutDownEngine();


		//��ȡ��ǰ����ĵ��� obj
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		//ToDo ����ֱ��������ȡ
		inline ImGuiLayer* GetImguiLayer() { return m_ImGuiLayer; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		//���unique window��ָ��ǰѡ�� window��ָ��  ������window ���ܲ�����GLFWʵ�ֵĿ��ܻ��ӱ������
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;

		

	};

	// ���������Ҫ��client�� Ҳ������Ϸ��ʵ�֡� ֻ��������������
	Application* CreateApplication();


}




