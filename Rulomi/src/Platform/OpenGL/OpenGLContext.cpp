#include "RulomiPch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"


namespace Rulomi {

    OpenGLContext::OpenGLContext(GLFWwindow* window)
		:m_WindowHandle(window)
	{
		RLM_CORE_ASSERT(m_WindowHandle, "Cur_Window is NULL");
	}
	void OpenGLContext::Init()
	{
		//���������ģ��������
		glfwMakeContextCurrent(m_WindowHandle);
		//init glad    glfw��include ʱ������һ��opengl�Ķ���eg��gl.h
		//����Ҫ��glfw �ĺ궨���һ��GLFW_INCLUDE_NONE
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RLM_CORE_ASSERT(status, "can not init GLAD��");

		RLM_CORE_INFO("OpenGL Info:");
		RLM_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		RLM_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		RLM_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}



}

