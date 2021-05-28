
#include"RulomiPch.h"
#include "Application.h"

#include "Log.h"

#include "Renderer/Renderer.h"
#include "Input.h"

#include <GLFW/glfw3.h>


namespace Rulomi {

#define BIND_EVENT_FN(x)  std::bind(&Application::x , this, std::placeholders::_1)

	 Application* Application::s_Instance = nullptr;

	//��ʼ����������
	Application::Application(const std::string& name)
	
	{
		//RLM_ASSERT(!s_Instance, "Can only has one app");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(name)));

		//����Ϊ������Ӧ�õĺ���   �������� callback��ʱ�� ���� OnEvent ����
		// ����Ǹ� windowdata ����callback ���� 
		m_Window->SetEventCallback(  std::bind(&Application::OnEvent, this, std::placeholders::_1) ); 

		//��ʼ����Ⱦ��
		Renderer::Init();

		//�Դ�һ��UI����layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		//�����ʱ�� m_Event ����Ҳ����ʼ��
		EventDispatcher dispatcher(e);
		// �����ж� �������¼������Ƿ� �� .Dispatch<T> ��T��������Ҫ��������һ�£�
		dispatcher.Dispatch<WindowCloseEvent>( std::bind(&Application::OnWindowClose, this, std::placeholders::_1) );
		RLM_CORE_INFO("{0}", e);

		//������window �йص�dispatcher ��������� ��������layer�ٴ����Ա�
		for (auto iterator_end = m_LayerStack.end(); iterator_end != m_LayerStack.begin(); ) 
		{
			//һ��overlayer ���˴�����ֹͣ����¼���Ӧ || Ҳ������껮��viewport ������Ϣ����
			if (e.Handled)
				break;
			//�����ص������¼����ȶ��� overlayer  ���������ÿ��layer �Լ�����
			(*--iterator_end)->OnEvent(e);
		}
	}

	void Application::ShutDownEngine()
	{
		m_Running = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}

	void Application::PopOverlay(Layer* layer)
	{
		m_LayerStack.PopOverLayer(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		//ֹͣ������ѭ��
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		//������ѭ��
		while (m_Running)
		{
			//time interval 
			float Currenttime = (float)glfwGetTime();
			TimeInterval timeInterval = Currenttime - m_LastFrameTime;
			m_LastFrameTime = Currenttime;
			//ˢ����Ⱦ����
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timeInterval);
			//��������layers ����ˢ��UI 
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

		    auto pos = Input::GetMousePosition();
			//RLM_CORE_ERROR("{0} , {1} ", pos.first, pos.second);
			//Input::s_Instance->GetMousePosition();
			m_Window->OnUpdate();
		}
	}
}

