#include "RulomiPch.h"
#include "RulomiCore/Input.h"

//按键响应由glfw提供
#include <GLFW/glfw3.h>
#include "RulomiCore/Application.h"


namespace Rulomi {

	// 初始化
	//由于这个input类是一个只有数据和方法的单例 
	//向上转型 upcast 动态绑定
	//指针调用？
	//全局静态变量必须要有定义 不然报错~！
   //Input* Input::s_Instance = new WindowsInput();


	bool Input::IsKeyPressed(int keycode)
	{
		//void 指针和具体类型指针之间的转换，例如void *转int *、char *转void *等；
		GLFWwindow* cur_window = static_cast<GLFWwindow*> ( Application::Get().GetWindow().GetNativeWindow() );
		//glfw需要知道是哪个window
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