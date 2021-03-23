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
		//���ص���һ��ָ�� ����windows���ڵ�ָ��
		//���� ����������WindowsWindow ���Զ�̬�󶨵� Window 
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
		
			//����ص�
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitalized = true;
		}

		m_Window = glfwCreateWindow( (int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);

		//�����ĳ�ʼ����abstructioning��
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		// VSync ��ʾ? 
		SetVSync(true);

		//Set GLFW callbacks??   ���Ҵ����ﴴ���¼� dispatch �� application 
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
			    //��ȡ��ǰ���ڵ����� ��Ӧevent ���޸�
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				// ������ط��� Eventcall back������ͱ�set���� Onevent   �����൱�ڵ��øú�����
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				// *void �Ļ� ����ʾ  ���ʽ������ָ�������������ͣ�void���������ģ���ָ��  ��������Ҫǿ��castһ��
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

		//��Щcallback ��GLFW�Զ����õ� ����Ҳ���Զ���ֵ��
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
		//swap һ��window��ǰ�� buffer����Щbuffer ����Ҫ�������ģ�
		//��ƽ̨���� �����context�����
		m_Context->SwapBuffers();
		
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		//glfwSwapInterval ���� ��ǰbuffer�� context��ˢ�¼��
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