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

		//创建场景
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
		//cc.main = false; //默认是开启 为true

	
		////
		//class CameraController : public ScriptableEntity
		//{
		//public:
		//	//读取相机位置
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
		//		//提出
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
		//	//创建 并且向上转型 
		//second_cam.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		//m_SceneHierarchyPanel.SetContext(m_Scene);

		//SpriteRendererComponent

		//纹理测试
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
		////sampler2D 是一种采样器 需要赋值的是 这个sampler 想要采样的纹理所绑定的槽位
		//std::dynamic_pointer_cast<OpenGLShader>(textureshader)->UploadUniformInt("u_Texture", 0);
	}
	static float dlt = 0.0f;

	void EditorLayer::OnAttach()
	{
		//frambuffer初始化
		FramebufferSpecification FbSpecifiation;
		//Attachements 表示需要哪几种 缓冲区
		FbSpecifiation.Attachements = { FramebufferTextureFmt::RGBA8, FramebufferTextureFmt::R_INTERGER ,FramebufferTextureFmt::Depth };
		FbSpecifiation.Width = 1280;
		FbSpecifiation.Height = 720;
		m_FrameBuffer = Framebuffer::Create(FbSpecifiation);
		//m_Texture2D = Texture2D::Create("Assets/textures/12.jpg");

		//创建场景
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
				//绘制
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
		//当 viewport resize的时候 //与之前不同 这个viewport变化过后 是同时刷新所有摄像机
		if (FramebufferSpecification spec = m_FrameBuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_FrameBuffer->ResizeBuffer((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			//Camera Control TO MOVE IT　
			m_orthographicCameraControler.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			//更新editor相机
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		
		//更新 相机位置 （初始化在Layer 成形之前) || 只有在
		if (m_viewportFocused)
			m_orthographicCameraControler.OnUpdate(deltTime);
		m_EditorCamera.OnUpdate(deltTime);
		
		Renderer2D::ResetStats();
		// 开始为FrameBuffer 填充内容但 显示放在 imgui
		m_FrameBuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
			m_FrameBuffer->ClearAttachment(1, -1);

			//Draw pixle
			m_Scene->OnUpdateEditor(deltTime, m_EditorCamera);

			// GetMousePos（） 也是获取全局坐标
			auto [mx, my] = ImGui::GetMousePos();
			//相减表示 鼠标在viewport 中的位置
			mx = mx - m_ViewportBounds[0].x;
			my = my - m_ViewportBounds[0].y;
			glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
			//将鼠标坐标切转换到纹理坐标  (OpenGL 与 texture 坐标相反)
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

		//样例UI
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &Dockspace_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		//设置dockspace的属性
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
	 
		//设置 其中每个dock的最小宽度
		style.WindowMinSize.x = 370.0f;

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		//这个是把数值设回去 在下一个dockspace中做操作保证为初始值
		//style.WindowMinSize.x = minWinSizeX;
		

		if (ImGui::BeginMenuBar())
		{
			//小选项
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


		//目的一实现 framebuffer的大小随着  viewport的大小改变
		ImGui::Begin("ViewPort");
		
			//这里面的是vieport 窗口内容的最大最小值
			ImVec2 viewportMinRegion = ImGui::GetWindowContentRegionMin();
			ImVec2 viewportMaxRegion = ImGui::GetWindowContentRegionMax();
			
			// 每个panel  CursorPos表示接下来imgui要在哪开始draw 这个地方包含了顶部的tag部分 因此实际viewport应当减去顶部tag高度37
			//全局坐标
			ImVec2  viewportOffset = ImGui::GetWindowPos();
			m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
			m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
			//RLM_CORE_FATAL("{0}, {1} ", viewportOffset.x, viewportOffset.y);

			m_viewportFocused = ImGui::IsWindowFocused();
			m_viewportHovered = ImGui::IsWindowHovered();
			// block 表示是否让imgui 层阻止event 向下传递
			// 在viewport 之外的其他地方应该阻止 event 的传递 --> 不阻止 场景控制
			// 即没有focus viewport 
			//但 当选中 viewport 但鼠标不 hover 的时候滚动 会影响其他 imgui
			//阻止 场景控制的条件是 没有选中viewport或者没有hover在上面
			Application::Get().GetImguiLayer()->BlockEvents( !m_viewportFocused && !m_viewportHovered );
			//获得窗口大小
			ImVec2 Curentviewportsize = ImGui::GetContentRegionAvail();
			m_ViewportSize = { Curentviewportsize.x, Curentviewportsize.y };
		 
			uint64_t textureID = m_FrameBuffer->GetColorTextureAttachmentRendererID();
			ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

			//获取imgui viewport（窗口） 的大小 
			//ImVec2 winodow_size = ImGui::GetWindowSize();
			////minbound 表示绘制区域的 左上角位置（在屏幕坐标系中）
			//ImVec2 minBound = ImGui::GetWindowPos();
			//minBound.x += viewportOffset.x;
			//minBound.y += viewportOffset.y-37;  //
			////通过加上viewport窗口的大小 将绘制区域的上限算出
			//ImVec2 maxBound = { minBound.x + winodow_size.x, minBound.y + winodow_size.y };
			////viewport的绘制区域 左上角与右下角（在屏幕坐标系中）
			//m_ViewportBounds[0] = { minBound.x, minBound.y };
			//m_ViewportBounds[1] = { maxBound.x, maxBound.y };

			// 通过选定右侧entity来显示gizmo
			Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
			if (selectedEntity && m_GizmoType != -1)
			{
				ImGuizmo::SetOrthographic(false);
				//SetDrawlist表示在当前window中绘制
				ImGuizmo::SetDrawlist();

				float windowWidth = (float)ImGui::GetWindowWidth();
				float windowHeight = (float)ImGui::GetWindowHeight();

				//设置view-port （x,y表示窗口起始位置) 后俩参数表示窗口大小
				ImGuizmo::SetRect(m_ViewportBounds[0].x,
					m_ViewportBounds[0].y, 
					m_ViewportBounds[1].x - m_ViewportBounds[0].x, 
					m_ViewportBounds[1].y - m_ViewportBounds[0].y);

				//<<Run time>>Camera  gizmo 出现的位置 相机+物体自身来决定  (V P 俩个矩阵)
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

				//移动和跳转gizmo的时候
				if (ImGuizmo::IsUsing())
				{
					//抽离矩阵  为什么不直接取组件里面的数据？因为组件里面的数据还没改啊！只是通过空间坐标变化获得了变化后的 3和1矩阵的值，现在要反向解3个组件的具体数值 
					glm::vec3 translation, rotation, scale;
					Math::DecomposeTransform(entTransformMtx, translation, rotation, scale);

					glm::vec3 deltaRotation = rotation - EntTransComp.rotation;
					//for transformation
					EntTransComp.position = translation;
					//for rotation （解决了 gimbal lock？why？）
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
		//如果不在imgui层阻止。则就会落到 editor层被响应
		m_orthographicCameraControler.OnEvent(event);
		m_EditorCamera.OnEvent(event);

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(RLM_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(RLM_BIND_EVENT_FN(EditorLayer::OnMousePressed));
	}

	//通过键盘轮询来实现 按键响应
	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		//return false 表示这个事件将不被处理 继续向下一层传递信息 GetRepeatCount 其实是一个flag值表示是否按住了当前键盘。与只点击一次做区分
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
			// Gizmos 正在使用gizmo的时候不能突然改变类型
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
		//return false; 为什么这个不要了？
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
	{			//	第一个表示默认显示文字内容
				// 第二个表示 真实想要使用的filter （后缀名） 这里有俩种
		std::string filepath = SelectFileWindow::OpenFile("Rulomi Scene (*.Rulomi)\0*.Rulomi\0*.Miku\0");
		if (!filepath.empty())
		{
			m_Scene = CreateRef<Scene>();
			//本质上是起到刷新的作用
			m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			//设置UI 以及 加载Entity
			m_SceneHierarchyPanel.SetContext(m_Scene);
			SceneSerializar serializer(m_Scene);
			serializer.DeSerialize(filepath);

		}
	}

	//选择一个文件覆盖？ 不能重命名？
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