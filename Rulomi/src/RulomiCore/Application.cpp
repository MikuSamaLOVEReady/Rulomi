
#include"RulomiPch.h"
#include "Application.h"

#include "Log.h"

#include <GLAD/glad.h>
#include "Input.h"

namespace Rulomi {

#define BIND_EVENT_FN(x)  std::bind(&Application::x , this, std::placeholders::_1)

	 Application* Application::s_Instance = nullptr;

	//��ʼ����������
	Application::Application()
	{
		//RLM_ASSERT(!s_Instance, "Can only has one app");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		//����Ϊ������Ӧ�õĺ���   �������� callback��ʱ�� ���� OnEvent ����
		// ����Ǹ� windowdata ����callback ���� 
		m_Window->SetEventCallback(  std::bind(&Application::OnEvent, this, std::placeholders::_1) ); 

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//Vertex Array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		float  vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f , 0.5f , 0.0f
		}; 
		// ����һ����ƽ̨�� VertexBuffer
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		//buffer layout abstuction
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		
		unsigned int indices[3] = {  0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3) );
		std::string vertexSouce = R"(
                     #version 330 core
					 layout(location = 0) in vec3 a_Position;
					 out vec3 v_Position;
					void main()
					{
					        v_Position = a_Position;
							gl_Position = vec4(a_Position,1.0);
					}
              )";
		std::string fragmentSouce = R"(
                     #version 330 core
					 layout(location = 0) out vec4 a_Color;
					 in vec3 v_Position;
					void main()
					{
							a_Color = vec4(v_Position,1.0 );
					}
              )";

		m_Shader.reset(new Shader(vertexSouce, fragmentSouce));

	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		//�����ʱ�� m_Event ����Ҳ����ʼ��
		EventDispatcher dispatcher(e);
		// �����ж� �������¼������Ƿ� �� .Dispatch<T> ��T��������Ҫ��������һ�£�
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		RLM_CORE_INFO("{0}", e);


		//������window �йص�dispatcher ��������� ��������layer�ٴ����Ա�
		for (auto iterator_end = m_LayerStack.end(); iterator_end != m_LayerStack.begin(); ) 
		{
			//�����ص������¼����ȶ��� overlayer  ���������ÿ��layer �Լ�����
			(*--iterator_end)->OnEvent(e);
			//һ��overlayer ���˴�����ֹͣ����¼���Ӧ
			if (e.Handled)
				break;
		}
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
		//WindowResizeEvent e(1280, 720);
		//RLM_CORE_TRACE(e);
		while (m_Running)
		{
			/*glClearColor((double)72/255, (double)209/255, (double)204/255, 1);*/

			glClearColor( 0.1f , 0.1f , 0.1f , 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			//�ٰ�VAB ������ͬʱ�󶨵�IBҲ�ᱻ�Զ���
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_ImGuiLayer->Begin();
			//��������layers ����ˢ��
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

