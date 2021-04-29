#include <Rulomi.h>
#include"RulomiCore/EntryPoint.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/glm.hpp"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Exmplayer :public Rulomi::Layer {
public:
	//这里设置的四个元素是 相机的属性 而非位置
	//初始化 编译shader
	Exmplayer()
		:Layer("MikuSama"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPostion(1.0f)
	{
		m_VertexArray.reset(Rulomi::VertexArray::Create());

		float  vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		// 创建一个跨平台的 VertexBuffer crete中自动判定
		m_VertexBuffer.reset(Rulomi::VertexBuffer::Create(vertices, sizeof(vertices)));

		//在创建buffer layout的时候 就确定 offset 和 layout
		Rulomi::BufferLayout layout = {
			{Rulomi::ShaderDataType::Float3, "a_Position" },
			{Rulomi::ShaderDataType::Float4, "a_Color" }
		};
		//每个VB 只能同时含有一个 layout
		m_VertexBuffer->SetLayout(layout);
		//需要根据layout设置 shader属性
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		
		unsigned int indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(Rulomi::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		std::string vertexSouce = R"(
                     #version 330 core
					 layout(location = 0) in vec3 a_Position;
					 layout(location = 1) in vec4 a_Color;

					uniform mat4 u_ViewProjection;
					uniform mat4 u_Transform;

					 out vec3 v_Position;
					 out vec4 v_Color;

					void main()
					{
					        v_Position = a_Position;
							v_Color = a_Color;
							gl_Position = u_ViewProjection *u_Transform* vec4(a_Position, 1.0);	
					}
              )";

		std::string fragmentSouce = R"(
                     #version 330 core
					 layout(location = 0) out vec4 a_Color;

					 uniform vec3 u_Color;

					 in vec4 v_Color;
					

					void main()
					{
							a_Color = vec4(u_Color, 1.0);
					}
              )";
		//这种没有单独文件处理的部分 则还是保留之前
	//	m_Shader.reset( Rulomi::Shader::Create(vertexSouce, fragmentSouce));
		m_Shader = Rulomi::Shader::Create("trangle_shader", vertexSouce, fragmentSouce);
		m_CashedShader.Add(m_Shader);

		//纹理测试
		m_SquareVA.reset(Rulomi::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Rulomi::Reference<Rulomi::VertexBuffer> squareVB;
		squareVB.reset(Rulomi::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Rulomi::ShaderDataType::Float3, "a_Position" },
			{ Rulomi::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Rulomi::Reference<Rulomi::IndexBuffer> squareIB;
		squareIB.reset(Rulomi::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		//frambuffer 初始化
		Rulomi::FramebufferSpecification FbSpecifiation;
		FbSpecifiation.Width = 1280;
		FbSpecifiation.Height = 720;
		m_FrameBuffer = Rulomi::Framebuffer::Create(FbSpecifiation);

		// 这些creat 都分装到 shader libray中了
		//m_TextureShader.reset(Rulomi::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
		//m_TextureShader.reset(Rulomi::Shader::Create("assets/shaders/Texture.glsl"));
		//m_TextureShader = Rulomi::Shader::Create();
		Rulomi::Reference<Rulomi::Shader> textureshader = m_CashedShader.Load("assets/shaders/Texture.glsl");
	    //m_CashedShader.Add(textureshader);

		m_Texture2D = Rulomi::Texture2D::Create("assets/textures/12.jpg");
		std::dynamic_pointer_cast<Rulomi::OpenGLShader>(textureshader)->Bind();
		//sampler2D 是一种采样器 需要赋值的是 这个sampler 想要采样的纹理所绑定的槽位
		std::dynamic_pointer_cast<Rulomi::OpenGLShader>(textureshader)->UploadUniformInt("u_Texture", 0);


	 }

	void OnUpdate(Rulomi::TimeInterval deltTime) override
	{

		RLM_Client_INFO("{0}", deltTime.getTimeMilliseconds());
		//当前这些更新 是根据 当前的帧率来跟新
		//应当设置为 ΔTime
		if (Rulomi::Input::IsKeyPressed(RLM_KEY_LEFT))
			m_CameraPostion.x -= m_CameraMoveSpeed*deltTime;
		else if (Rulomi::Input::IsKeyPressed(RLM_KEY_RIGHT))
			m_CameraPostion.x += m_CameraMoveSpeed * deltTime;
		if (Rulomi::Input::IsKeyPressed(RLM_KEY_UP))
			m_CameraPostion.y += m_CameraMoveSpeed * deltTime;
		else if (Rulomi::Input::IsKeyPressed(RLM_KEY_DOWN))
			m_CameraPostion.y -= m_CameraMoveSpeed * deltTime;

		if (Rulomi::Input::IsKeyPressed(RLM_KEY_A))
			m_CameraRotationDegree += m_CameraRotationSpeed * deltTime;
		if(Rulomi::Input::IsKeyPressed(RLM_KEY_D))
			m_CameraRotationDegree -= m_CameraRotationSpeed * deltTime;


		//event polling
		if (Rulomi::Input::IsKeyPressed(RLM_KEY_BACKSPACE))
			RLM_Client_INFO("RLM_KEY_BACKSPACE ！！！！！！！！！！！！！！！！");


		// 开始为FrameBuffer 填充内容但 显示放在 imgui
		m_FrameBuffer->Bind();

		Rulomi::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Rulomi::RenderCommand::Clear();
		//初始化相机位置
		m_Camera.SetPosition(m_CameraPostion);
		m_Camera.SetRotation(m_CameraRotationDegree);


		//渲染器全抽象
		//详见 Render class设计
		Rulomi::Renderer::BeginScene(m_Camera);

		//设置每个obj的 transform matix 让他们进入世界坐标
		//放缩到0.1倍
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Rulomi::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Rulomi::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_Color);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++) 
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				//绘制 
				Rulomi::Renderer::Submit(m_Shader, m_VertexArray,transform);
			}
		}

		//shder 管理类
		auto textureshader = m_CashedShader.GetShaderByName("Texture");
		m_Texture2D->Bind();
		Rulomi::Renderer::Submit(textureshader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//可以绑定多套shader 和 VA
		Rulomi::Renderer::EndScene();

		m_FrameBuffer->UnBind();
	}

	void OnEvent(Rulomi::Event& event) override
	{
		//RLM_Client_TRACE("{0} Layer EVENT By Exmplayer ", event);
	}

	virtual void OnImGuiRender() override
	{

		//初始化 docking space
		static bool Dockspace_open = true;
		static bool opt_fullscreen = true;
 	
		//static bool opt_padding = false;	//这个是干啥
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		//if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &Dockspace_open, window_flags);
		//if (!opt_padding)
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace  内容填充？
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		if (ImGui::BeginMenuBar())
		{
			//小选项
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				//ImGui::MenuItem("Padding", NULL, &opt_padding);
				//ImGui::Separator();

				//if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
				//if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				//if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
				//if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				//if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				//ImGui::Separator();
				if ( ImGui::MenuItem("close") ) { Rulomi::Application::Get().ShutDownEngine(); }

				//if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
					//*p_open = false;
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

			ImGui::Begin("WWWWW");
				//color picker
				ImGui::ColorEdit3("Square Color", glm::value_ptr(m_Color));
				ImGui::Text("Renderer2D Stats:");

				//读取frame buffer 中的color Texture部分
				uint32_t textureID = m_FrameBuffer->GetColorTextureAttachmentRendererID();
				ImGui::Image( (void*)textureID, ImVec2{ 1280, 720 });

			ImGui::End();


		ImGui::End();


	}

private:
	//三角形
	std::shared_ptr<Rulomi::Shader> m_Shader;
	std::shared_ptr<Rulomi::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Rulomi::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Rulomi::VertexArray> m_VertexArray;
	
	//纹理矩形
	std::shared_ptr<Rulomi::Shader> m_FlatColorShader;
	std::shared_ptr<Rulomi::VertexArray> m_SquareVA;
	Rulomi::Reference<Rulomi::Texture2D> m_Texture2D;

	//Framebuffer 
	Rulomi::Reference <Rulomi::Framebuffer> m_FrameBuffer;

	//shader 缓存
	Rulomi::ShaderLibrary m_CashedShader;

	//摄像机系统
	Rulomi::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPostion;
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotationDegree = 0.0f;
	float m_CameraRotationSpeed = 8.0f;
	// color picker
	glm::vec3 m_Color = { 0.2f, 0.3f, 0.8f };


};


class Sandbox : public Rulomi::Application {

public:
	Sandbox() {

		PushLayer(new Exmplayer());
		//PushOverlay(new Rulomi::ImGuiLayer());

	}

	~Sandbox() {

	}

};

//引擎内部的函数的申明 由游戏对象定义
Rulomi::Application* Rulomi::CreateApplication()
{
	return new Sandbox();
}


