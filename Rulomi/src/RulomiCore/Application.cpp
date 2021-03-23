
#include"RulomiPch.h"
#include "Application.h"

#include "Log.h"

#include <GLAD/glad.h>
#include "Input.h"

namespace Rulomi {

#define BIND_EVENT_FN(x)  std::bind(&Application::x , this, std::placeholders::_1)

	 Application* Application::s_Instance = nullptr;

	//初始化整个引擎
	Application::Application()
	{
		//RLM_ASSERT(!s_Instance, "Can only has one app");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		//参数为处理响应用的函数   即当窗口 callback的时候 调用 OnEvent 函数
		// 这个是给 windowdata 设置callback 函数 
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
		// 创建一个跨平台的 VertexBuffer
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
		//构造的时候 m_Event 类型也被初始化
		EventDispatcher dispatcher(e);
		// 这里判断 发出的事件类型是否 与 .Dispatch<T> 中T（我们想要检测的类型一致）
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		RLM_CORE_INFO("{0}", e);


		//被处理window 有关的dispatcher 处理完过后 还将交给layer再处理以边
		for (auto iterator_end = m_LayerStack.end(); iterator_end != m_LayerStack.begin(); ) 
		{
			//函数回调，将事件优先丢给 overlayer  这个处理是每个layer 自己在做
			(*--iterator_end)->OnEvent(e);
			//一旦overlayer 有人处理则停止这个事件响应
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
		//停止引擎主循环
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
			//再绑定VAB 后与他同时绑定的IB也会被自动绑定
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_ImGuiLayer->Begin();
			//遍历所有layers 并且刷新
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

