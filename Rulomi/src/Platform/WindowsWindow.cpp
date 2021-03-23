#include "RulomiPch.h"
#include "WindowsWindow.h"

#include"RulomiCore/Events/ApplicationEvent.h"
#include"RulomiCore/Events/KeyEvent.h"
#include"RulomiCore/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"


namespace Rulomi {

	static bool s_GLFWInitalized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		RLM_CORE_ERROR("GLFW Error ({0}):  {1}", error, description);
	};

    // Window
	Window* Window::Create(const WindowProps& props)
	{
		//返回的是一个指向 子类windows窗口的指针
		//但是 返回类型是WindowsWindow 可以动态绑定到 Window 
		return new WindowsWindow(props);
	}


	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title		=	props.Title;
		m_Data.Width  = props.Width;
		m_Data.Height = props.Height;
		RLM_CORE_TRACE("window attributes {0} ( {1} , {2} )", props.Title, props.Width, props.Height);

		if (!s_GLFWInitalized)
		{
			//glfw initialization
			int success = glfwInit();
			RLM_CORE_ASSERT(success, "can not init GLFW");
		
			//错误回调
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitalized = true;
		}

		m_Window = glfwCreateWindow( (int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);

		//上下文初始化（abstructioning）
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		// VSync 表示? 
		SetVSync(true);

		//Set GLFW callbacks??   并且从这里创建事件 dispatch 给 application 
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
			    //获取当前窗口的数据 响应event 后修改
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				// 像这个地方的 Eventcall back函数早就被set成了 Onevent   这里相当于调用该函数！
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				// *void 的话 会提示  表达式必须是指向完整对象类型（void不是完整的）的指针  所以这里要强行cast一下
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{

				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key , 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleaseEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key,1);
						data.EventCallback(event);
						break;
					}
				}
			});

		//这些callback 是GLFW自动调用的 参数也是自动赋值的
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event( (float)xoffset, (float)yoffset );
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int charcter) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(charcter);
				data.EventCallback(event);
			});

	}

	void WindowsWindow::Shutdown() 
	{
		glfwDestroyWindow(m_Window);
	}

	//refresh our window
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		//swap 一个window的前后 buffer（这些buffer 都需要有上下文）
		//跨平台考虑 抽象出context这个类
		m_Context->SwapBuffers();
		
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		//glfwSwapInterval 设置 当前buffer的 context的刷新间隔
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const 
	{
		return m_Data.VSync;
	}








}