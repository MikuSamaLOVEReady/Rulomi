#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

#include "RulomiCore/ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"



namespace Rulomi {

	//application ��������ֻ����һ������siglten
	class  RULOMI_API Application
	{
	public: 
		Application();
		//C++��base��Ϊɶ����Ҫ�����ó�virtual��
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		//��ȡ��ǰ����ĵ��� obj
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		//���unique window��ָ��ǰѡ�� window��ָ��
		std::unique_ptr<Window> m_Window;


		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	      
		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		static Application* s_Instance;

		

	};

	// ���������Ҫ��client�� Ҳ������Ϸ��ʵ�֡� ֻ��������������
	Application* CreateApplication();


}



