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
		//创建上下文，抽象出来
		glfwMakeContextCurrent(m_WindowHandle);
		//init glad    glfw在include 时候会带有一点opengl的东西eg：gl.h
		//所以要让glfw 的宏定义多一个GLFW_INCLUDE_NONE
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RLM_CORE_ASSERT(status, "can not init GLAD！");

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

