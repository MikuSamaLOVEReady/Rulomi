#include "RulomiPch.h"
#include "RulomiCore/Input.h"

//������Ӧ��glfw�ṩ
#include <GLFW/glfw3.h>
#include "RulomiCore/Application.h"


namespace Rulomi {

	// ��ʼ��
	//�������input����һ��ֻ�����ݺͷ����ĵ��� 
	//����ת�� upcast ��̬��
	//ָ����ã�
	//ȫ�־�̬��������Ҫ�ж��� ��Ȼ����~��
   //Input* Input::s_Instance = new WindowsInput();


	bool Input::IsKeyPressed(int keycode)
	{
		//void ָ��;�������ָ��֮���ת��������void *תint *��char *תvoid *�ȣ�
		GLFWwindow* cur_window = static_cast<GLFWwindow*> ( Application::Get().GetWindow().GetNativeWindow() );
		//glfw��Ҫ֪�����ĸ�window
		int state = glfwGetKey(cur_window, keycode);
		RLM_CORE_ERROR("{0}+++++++++++++", keycode);
		return state == GLFW_PRESS || state== GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		GLFWwindow* cur_window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(cur_window, button);
		return state == GLFW_PRESS;
	}

	float Input::GetMouseX()
	{
		GLFWwindow* cur_window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(cur_window, &xpos, &ypos);
		return xpos;
	}

	float Input::GetMouseY()
	{
		GLFWwindow* cur_window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(cur_window, &xpos, &ypos);
		return ypos;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		GLFWwindow* cur_window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(cur_window, &xpos, &ypos);
		return { (float)xpos, (float)ypos  };
	}




}