#include "EditorLayer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

#include "RulomiCore/Scene/SceneSerializar.h"
#include "RulomiCore/PlatformUtil/Utils.h"
#include "ImGuizmo/ImGuizmo.h"
#include "RulomiCore/MathEX/Math.h"

namespace Rulomi {
	EditorLayer::EditorLayer()
		:Layer("EditorLayer"), m_orthographicCameraControler( 1280.0f / 720.0f )
	{
		/*m_VertexArray.reset( VertexArray::Create());
		//m_VertexArray.reset()

		float  vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float4, "a_Color" }
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		unsigned int indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
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

		m_Shader = Shader::Create("trangle_shader", vertexSouce, fragmentSouce);
		
		m_CashedShader.Add(m_Shader);*/

		//��������
		//m_Scene = CreateRef<Scene>();

		// Entity
		//Entity first_entity = m_Scene->CreateEntity("First");
		//first_entity.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f,1.0f,0.0f,1.0f });
		//m_firstEntity = first_entity;

		//main_cam = m_Scene->CreateEntity("camera");
		////glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f) 
		//main_cam.AddComponent<CameraComponent>();

		//second_cam = m_Scene->CreateEntity("second_camera");
		//auto& cc  = second_cam.AddComponent<CameraComponent>();
		//cc.main = false; //Ĭ���ǿ��� Ϊtrue

	
		////
		//class CameraController : public ScriptableEntity
		//{
		//public:
		//	//��ȡ���λ��
		//	void OnCreate() override
		//	{
		//		auto& transform = GetComponent<TransformComponent>().position;
		//		transform.x = rand() % 10 - 5.0f;
		//	}
		//	
		//	void OnDestroy() override
		//	{
		//	}

		//	void OnUpdate(TimeInterval ts) override
		//	{
		//		//���
		//		auto& transform = GetComponent<TransformComponent>().position;

		//		float speed = 5.0f;
		//		if (Input::IsKeyPressed(RLM_KEY_A))
		//			transform.x -= speed * ts;
		//		if (Input::IsKeyPressed(RLM_KEY_D))
		//			transform.x += speed * ts;
		//		if (Input::IsKeyPressed(RLM_KEY_W))
		//			transform.y += speed * ts;
		//		if (Input::IsKeyPressed(RLM_KEY_S))
		//			transform.y -= speed * ts;
		//	}
		//};
		//	//���� ��������ת�� 
		//second_cam.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		//m_SceneHierarchyPanel.SetContext(m_Scene);

		//SpriteRendererComponent

		//�������
		//m_SquareVA.reset(VertexArray::Create());
		//float squareVertices[5 * 4] = {
		//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		//	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		//	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		//	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		//};

		//Reference<VertexBuffer> squareVB;
		//squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		//squareVB->SetLayout({
		//	{ ShaderDataType::Float3, "a_Position" },
		//	{ ShaderDataType::Float2, "a_TexCoord" }
		//	});
		//m_SquareVA->AddVertexBuffer(squareVB);

		//uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		//Reference<IndexBuffer> squareIB;
		//squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		//m_SquareVA->SetIndexBuffer(squareIB);

		//Reference<Shader> textureshader = m_CashedShader.Load("assets/shaders/Texture.glsl");
		////m_CashedShader.Add(textureshader);

		//std::dynamic_pointer_cast<OpenGLShader>(textureshader)->Bind();
		////sampler2D ��һ�ֲ����� ��Ҫ��ֵ���� ���sampler ��Ҫ�������������󶨵Ĳ�λ
		//std::dynamic_pointer_cast<OpenGLShader>(textureshader)->UploadUniformInt("u_Texture", 0);
	}
	static float dlt = 0.0f;

	void EditorLayer::OnAttach()
	{
		//frambuffer��ʼ��
		FramebufferSpecification FbSpecifiation;
		//Attachements ��ʾ��Ҫ�ļ��� ������
		FbSpecifiation.Attachements = { FramebufferTextureFmt::RGBA8, FramebufferTextureFmt::R_INTERGER ,FramebufferTextureFmt::Depth };
		FbSpecifiation.Width = 1280;
		FbSpecifiation.Height = 720;
		m_FrameBuffer = Framebuffer::Create(FbSpecifiation);
		//m_Texture2D = Texture2D::Create("Assets/textures/12.jpg");

		//��������
		m_Scene = CreateRef<Scene>();
		// NOT entity
		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

		// Entity
		/*auto square = m_Scene->CreateEntity("Green Square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

		auto redSquare = m_Scene->CreateEntity("Red Square");
		redSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

		m_SquareEntity = square;

		



		main_cam = m_Scene->CreateEntity("Camera A");
		main_cam.AddComponent<CameraComponent>();

		second_cam = m_Scene->CreateEntity("Camera B");
		auto& cc = second_cam.AddComponent<CameraComponent>();*/

		/*
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				//����
				Rulomi::Renderer::Submit(m_Shader, m_VertexArray,transform);
			}
		}
		*/

 

		class CameraController : public ScriptableEntity
		{
		public:
			virtual void OnCreate() override
			{
				auto& translation = GetComponent<TransformComponent>().position;
				translation.x = rand() % 10 - 5.0f;
			}

			virtual void OnDestroy() override
			{
			}

			virtual void OnUpdate(TimeInterval ts) override
			{
				auto& transform = GetComponent<TransformComponent>().position;
				float speed = 5.0f;
				if (Input::IsKeyPressed(RLM_KEY_A))
					transform.x -= speed * ts;
				if (Input::IsKeyPressed(RLM_KEY_D))
					transform.x += speed * ts;
				if (Input::IsKeyPressed(RLM_KEY_W))
					transform.y += speed * ts;
				if (Input::IsKeyPressed(RLM_KEY_S))
					transform.y -= speed * ts;
			}
		};

		/*main_cam.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		second_cam.AddComponent<NativeScriptComponent>().Bind<CameraController>();*/


		m_SceneHierarchyPanel.SetContext(m_Scene);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(TimeInterval deltTime)
	{
		dlt = deltTime.getTimeMilliseconds();
		//�� viewport resize��ʱ�� //��֮ǰ��ͬ ���viewport�仯���� ��ͬʱˢ�����������
		if (FramebufferSpecification spec = m_FrameBuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_FrameBuffer->ResizeBuffer((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			//Camera Control TO MOVE IT��
			m_orthographicCameraControler.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			//����editor���
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		
		//���� ���λ�� ����ʼ����Layer ����֮ǰ) || ֻ����
		if (m_viewportFocused)
			m_orthographicCameraControler.OnUpdate(deltTime);
		m_EditorCamera.OnUpdate(deltTime);
		
		Renderer2D::ResetStats();
		// ��ʼΪFrameBuffer ������ݵ� ��ʾ���� imgui
		m_FrameBuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
			m_FrameBuffer->ClearAttachment(1, -1);

			//Draw pixle
			m_Scene->OnUpdateEditor(deltTime, m_EditorCamera);

			// GetMousePos���� Ҳ�ǻ�ȡȫ������
			auto [mx, my] = ImGui::GetMousePos();
			//�����ʾ �����viewport �е�λ��
			mx = mx - m_ViewportBounds[0].x;
			my = my - m_ViewportBounds[0].y;
			glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
			//�����������ת������������  (OpenGL �� texture �����෴)
			my = viewportSize.y - my;
			int  MouseX = int(mx);
			int  MouseY = int(my);
			//RLM_CORE_DEBUG("{0} ,{1}", MouseX, MouseY);

			if(MouseX>=0 && MouseY>= 0 && MouseX<(int)viewportSize.x && MouseY < (int)viewportSize.y)
			{
				int pixelData = m_FrameBuffer->ReadPixel(1, MouseX, MouseY);
				//RLM_CORE_DEBUG("Pixel data = {0}", pixelData);
				m_HoveredEntity = pixelData == -1 ? Entity() : Entity( (entt::entity)pixelData, m_Scene.get() );
			}
			
		m_FrameBuffer->UnBind(); 
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool Dockspace_open = true;
		static bool opt_fullscreen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
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

		//����UI
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &Dockspace_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		//����dockspace������
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
	 
		//���� ����ÿ��dock����С���
		style.WindowMinSize.x = 370.0f;

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		//����ǰ���ֵ���ȥ ����һ��dockspace����������֤Ϊ��ʼֵ
		//style.WindowMinSize.x = minWinSizeX;
		

		if (ImGui::BeginMenuBar())
		{
			//Сѡ��
			if (ImGui::BeginMenu("Options"))
			{
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				if (ImGui::MenuItem("close")) 
				{
					Application::Get().ShutDownEngine(); 
				}

				if (ImGui::MenuItem("Open..."))
				{
					OpenScene();
				}

				if (ImGui::MenuItem("Save as..."))
				{
					SaveSceneAs();
				}

				if (ImGui::MenuItem("Creat New Scene"))
				{
					NewScene();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	
		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Stats");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls (render task): %d", stats.DrawCalls);
		//ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices number: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices number: %d", stats.GetTotalIndexCount());
		ImGui::Text("Delta Time: %f", dlt);

		ImGui::End();


		//Ŀ��һʵ�� framebuffer�Ĵ�С����  viewport�Ĵ�С�ı�
		ImGui::Begin("ViewPort");
		
			//���������vieport �������ݵ������Сֵ
			ImVec2 viewportMinRegion = ImGui::GetWindowContentRegionMin();
			ImVec2 viewportMaxRegion = ImGui::GetWindowContentRegionMax();
			
			// ÿ��panel  CursorPos��ʾ������imguiҪ���Ŀ�ʼdraw ����ط������˶�����tag���� ���ʵ��viewportӦ����ȥ����tag�߶�37
			//ȫ������
			ImVec2  viewportOffset = ImGui::GetWindowPos();
			m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
			m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
			//RLM_CORE_FATAL("{0}, {1} ", viewportOffset.x, viewportOffset.y);

			m_viewportFocused = ImGui::IsWindowFocused();
			m_viewportHovered = ImGui::IsWindowHovered();
			// block ��ʾ�Ƿ���imgui ����ֹevent ���´���
			// ��viewport ֮��������ط�Ӧ����ֹ event �Ĵ��� --> ����ֹ ��������
			// ��û��focus viewport 
			//�� ��ѡ�� viewport ����겻 hover ��ʱ����� ��Ӱ������ imgui
			//��ֹ �������Ƶ������� û��ѡ��viewport����û��hover������
			Application::Get().GetImguiLayer()->BlockEvents( !m_viewportFocused && !m_viewportHovered );
			//��ô��ڴ�С
			ImVec2 Curentviewportsize = ImGui::GetContentRegionAvail();
			m_ViewportSize = { Curentviewportsize.x, Curentviewportsize.y };
		 
			uint64_t textureID = m_FrameBuffer->GetColorTextureAttachmentRendererID();
			ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

			//��ȡimgui viewport�����ڣ� �Ĵ�С 
			//ImVec2 winodow_size = ImGui::GetWindowSize();
			////minbound ��ʾ��������� ���Ͻ�λ�ã�����Ļ����ϵ�У�
			//ImVec2 minBound = ImGui::GetWindowPos();
			//minBound.x += viewportOffset.x;
			//minBound.y += viewportOffset.y-37;  //
			////ͨ������viewport���ڵĴ�С ������������������
			//ImVec2 maxBound = { minBound.x + winodow_size.x, minBound.y + winodow_size.y };
			////viewport�Ļ������� ���Ͻ������½ǣ�����Ļ����ϵ�У�
			//m_ViewportBounds[0] = { minBound.x, minBound.y };
			//m_ViewportBounds[1] = { maxBound.x, maxBound.y };

			// ͨ��ѡ���Ҳ�entity����ʾgizmo
			Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
			if (selectedEntity && m_GizmoType != -1)
			{
				ImGuizmo::SetOrthographic(false);
				//SetDrawlist��ʾ�ڵ�ǰwindow�л���
				ImGuizmo::SetDrawlist();

				float windowWidth = (float)ImGui::GetWindowWidth();
				float windowHeight = (float)ImGui::GetWindowHeight();

				//����view-port ��x,y��ʾ������ʼλ��) ����������ʾ���ڴ�С
				ImGuizmo::SetRect(m_ViewportBounds[0].x,
					m_ViewportBounds[0].y, 
					m_ViewportBounds[1].x - m_ViewportBounds[0].x, 
					m_ViewportBounds[1].y - m_ViewportBounds[0].y);

				//<<Run time>>Camera  gizmo ���ֵ�λ�� ���+��������������  (V P ��������)
				//Entity mainCame = m_Scene->GetMainCamera();
				//const auto& camera = mainCame.GetComponent<CameraComponent>().camera;
				//const glm::mat4& cameraProjection = camera.GetProjection();
				//glm::mat4 cameraView = glm::inverse(mainCame.GetComponent<TransformComponent>().GetTransformMtx());

				//Editor camera
				const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
				glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

				//Entity transform
				TransformComponent& EntTransComp = selectedEntity.GetComponent<TransformComponent>();
				glm::mat4  entTransformMtx = EntTransComp.GetTransformMtx();

				//draw call
				ImGuizmo::Manipulate(glm::value_ptr(cameraView),
					glm::value_ptr(cameraProjection),
					(ImGuizmo::OPERATION)m_GizmoType,
					ImGuizmo::LOCAL,glm::value_ptr(entTransformMtx) );

				//�ƶ�����תgizmo��ʱ��
				if (ImGuizmo::IsUsing())
				{
					//�������  Ϊʲô��ֱ��ȡ�����������ݣ���Ϊ�����������ݻ�û�İ���ֻ��ͨ���ռ�����仯����˱仯��� 3��1�����ֵ������Ҫ�����3������ľ�����ֵ 
					glm::vec3 translation, rotation, scale;
					Math::DecomposeTransform(entTransformMtx, translation, rotation, scale);

					glm::vec3 deltaRotation = rotation - EntTransComp.rotation;
					//for transformation
					EntTransComp.position = translation;
					//for rotation ������� gimbal lock��why����
					EntTransComp.rotation += deltaRotation;
					//for scale
					EntTransComp.scale = scale;
				}

			}
			ImGui::End();
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		//�������imgui����ֹ����ͻ��䵽 editor�㱻��Ӧ
		m_orthographicCameraControler.OnEvent(event);
		m_EditorCamera.OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(RLM_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(RLM_BIND_EVENT_FN(EditorLayer::OnMousePressed));
	}

	//ͨ��������ѯ��ʵ�� ������Ӧ
	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		//return false ��ʾ����¼����������� ��������һ�㴫����Ϣ GetRepeatCount ��ʵ��һ��flagֵ��ʾ�Ƿ�ס�˵�ǰ���̡���ֻ���һ��������
		if (e.GetRepeatCount() > 0)
			return false;
		bool control = Input::IsKeyPressed(RLM_KEY_LEFT_CONTROL) || Input::IsKeyPressed(RLM_KEY_RIGHT_CONTROL);
		bool shift = Input::IsKeyPressed(RLM_KEY_LEFT_SHIFT) || Input::IsKeyPressed(RLM_KEY_RIGHT_SHIFT);
		switch (e.GetKeyCode())
		{
			case  RLM_KEY_N:
			{
				if (control)
					NewScene();
				break;
			}
			case  RLM_KEY_O:
			{
				if (control)
					OpenScene();
				break;
			}
			case  RLM_KEY_S:
			{
				if (control)
					SaveSceneAs();
				break;
			}
			// Gizmos ����ʹ��gizmo��ʱ����ͻȻ�ı�����
			case RLM_KEY_Q:
			{
				if(!ImGuizmo::IsUsing())
					m_GizmoType = -1;
				break;
			}
			case RLM_KEY_W:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			}
			case RLM_KEY_E:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			}
			case RLM_KEY_R:
			{
				if (!ImGuizmo::IsUsing())
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
				break;
			}
		}
		//return false; Ϊʲô�����Ҫ�ˣ�
	}

	bool EditorLayer::OnMousePressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == RLM_MOUSE_BUTTON_LEFT && m_viewportHovered)
		{
			if( !ImGuizmo::IsOver())
				m_SceneHierarchyPanel.SelectedEntity(m_HoveredEntity);
		}
		return  false;
	}

	//
	void EditorLayer::NewScene()
	{
		m_Scene = CreateRef<Scene>();
		m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_Scene);
	}

	void EditorLayer::OpenScene()
	{			//	��һ����ʾĬ����ʾ��������
				// �ڶ�����ʾ ��ʵ��Ҫʹ�õ�filter ����׺���� ����������
		std::string filepath = SelectFileWindow::OpenFile("Rulomi Scene (*.Rulomi)\0*.Rulomi\0*.Miku\0");
		if (!filepath.empty())
		{
			m_Scene = CreateRef<Scene>();
			//����������ˢ�µ�����
			m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			//����UI �Լ� ����Entity
			m_SceneHierarchyPanel.SetContext(m_Scene);
			SceneSerializar serializer(m_Scene);
			serializer.DeSerialize(filepath);

		}
	}

	//ѡ��һ���ļ����ǣ� ������������
	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = SelectFileWindow::SaveFile("Rulomi Scene (*.Rulomi)\0*.Rulomi\0");
		if (!filepath.empty())
		{
			SceneSerializar serializer(m_Scene);
			serializer.Serialize(filepath);
		}
	}

	EditorLayer::~EditorLayer()
	{
	}

}