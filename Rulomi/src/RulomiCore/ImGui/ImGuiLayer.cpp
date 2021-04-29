#include "RulomiPch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
//#include "Platform/OpenGL/imgui_OpenGLRenderer.h"
//直接包含全部 实现和 输入字符匹配
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "RulomiCore/Application.h"
#include "RulomiCore/Core.h"

//临时存储 现在glfw只有管控窗体的函数
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include"ImGuizmo.h"

namespace Rulomi {

	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}


	//对layer 做一些初始化操作
	void ImGuiLayer::OnAttach()
	{ 
		//初始化一个Imgui 界面 Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		//SetDarkThemeColors(); 可通过这个设置imgui组件细节颜色

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		//shader 语言版本
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	//// 主循环每次都调用一次
	//void ImGuiLayer::OnUpdate()
	//{

	//	//begin
	//	// new frame 之前需要一个context which implemented in OnAttach method
	//	ImGui_ImplOpenGL3_NewFrame();
	//	ImGui::NewFrame();

	//	//这部分交给 on_imgui render
	//	static bool show = true;
	//	ImGui::ShowDemoWindow(&show);

	//	//End() -- Rendering
	//
	//}

	//Setup Dear ImGui context
	void ImGuiLayer::Begin() 
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();

	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	//imgui 层blocking event
	void ImGuiLayer::OnEvent(Event& event)
	{
		//这里会默认操作 完imgui的动作之后选择 是否把这个事件标志为handled
		if (m_BlockEvents) 
		{
			//选择将 鼠标和键盘 全部阻塞
			//WantCaptureMouse 表示 imgui想要使用 鼠标事件
			ImGuiIO& io = ImGui::GetIO();
			//IMGUI 想要处理 X事件 且该事件 是同一类型 则不向下 传递
			event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
		
	}


	void ImGuiLayer::End() 
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2( (float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		//Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	


	//bool OnKeyTypedEvent(KeyTypedEvent& e);

}