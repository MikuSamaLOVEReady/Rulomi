
#include"RulomiPch.h"
#include "Application.h"

#include "Log.h"


#include "Renderer/Renderer.h"
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

		//Vertex Array （ABS)
		//glGenVertexArrays(1, &m_VertexArray);
		//glBindVertexArray(m_VertexArray);

		m_VertexArray.reset(VertexArray::Create());

		float  vertices[3 * 7] = {
		    -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		}; 
		// 创建一个跨平台的 VertexBuffer crete中自动判定
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	    //在创建buffer layout的时候 就确定 offset 和 layout
	    BufferLayout layout = {
	    	{ ShaderDataType::Float3, "a_Position" },
	    	{ ShaderDataType::Float4, "a_Color" }
	    };
	    //每个VB 只能同时含有一个 layout
	    m_VertexBuffer->SetLayout(layout);
		//需要根据layout设置 shader属性
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		//buffer layout abstuction
		//glEnableVertexAttribArray(0);
		//第一个参数是激活第几个属性ID 
		//第二个参数是这个属性由几个数组成 
		//第三个 这几个数字的类型
		//第四个 normalized 是否开启
		//第五个 stride 表示 每个顶点的总容量大小 （eg 位置坐标3个float 颜色4个float 纹理 3个float 一共10个） 
		// stride 表示将指针向后移动多少个 bytes才能读取下一套数据
		//第五个表示offset 当stride过后，现在这个指针需要向后移动多少个单位才能读取到下一套属性。
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		
		unsigned int indices[3] = {  0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3) );
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		std::string vertexSouce = R"(
                     #version 330 core
					 layout(location = 0) in vec3 a_Position;
					 layout(location = 1) in vec4 a_Color;

					 out vec3 v_Position;
					 out vec4 v_Color;

					void main()
					{
					        v_Position = a_Position;
							v_Color = a_Color;
							gl_Position = vec4(a_Position,1.0);
					}
              )";

		std::string fragmentSouce = R"(
                     #version 330 core
					 layout(location = 0) out vec4 a_Color;
					 in vec3 v_Position;
					 in vec4 v_Color;
					void main()
					{
							a_Color = vec4(v_Position,1.0 );
							a_Color = v_Color;
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
		
		while (m_Running)
		{
			/*glClearColor((double)72/255, (double)209/255, (double)204/255, 1);*/
			//glClearColor( 0.1f , 0.1f , 0.1f , 1);
			//glClear(GL_COLOR_BUFFER_BIT);
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			//渲染器全抽象
			//详见 Render class设计
			Renderer::BeginScene();

			//绘制
			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			//可以绑定多套shader 和 VA


			//
			Renderer::EndScene();

			 
			//m_Shader->Bind();
			//m_VertexArray->Bind();
			//glBindVertexArray(m_VertexArray);
			//glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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

