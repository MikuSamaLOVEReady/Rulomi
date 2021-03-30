#include <Rulomi.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/glm.hpp"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Exmplayer :public Rulomi::Layer {
public:
	//这里设置的四个元素是 相机的属性 而非位置
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

		m_Shader.reset( Rulomi::Shader::Create(vertexSouce, fragmentSouce));




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

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Rulomi::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));
		m_Texture2D = Rulomi::Texture2D::Create("assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<Rulomi::OpenGLShader>(m_TextureShader)->Bind();
		//sampler2D 是一种采样器 需要赋值的是 这个sampler 想要采样的纹理所绑定的槽位
		std::dynamic_pointer_cast<Rulomi::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);


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
		
		m_Texture2D->Bind();
		Rulomi::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//可以绑定多套shader 和 VA
		Rulomi::Renderer::EndScene();
	}

	void OnEvent(Rulomi::Event& event) override
	{
		//RLM_Client_TRACE("{0} Layer EVENT By Exmplayer ", event);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("WWWWW");
		//color picker
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_Color));
		ImGui::End();
	}

private:
	//三角形
	std::shared_ptr<Rulomi::Shader> m_Shader;
	std::shared_ptr<Rulomi::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Rulomi::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Rulomi::VertexArray> m_VertexArray;
	

	//
	std::shared_ptr<Rulomi::Shader> m_FlatColorShader, m_TextureShader;
	std::shared_ptr<Rulomi::VertexArray> m_SquareVA;
	Rulomi::Reference<Rulomi::Texture2D> m_Texture2D;

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


