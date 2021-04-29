#include "RulomiPch.h"
//utilse��Ŀ¼��ʽ��һ��
#include "RulomiCore/PlatformUtil/Utils.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>

//���window handle-->
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "RulomiCore/Application.h"

namespace Rulomi {

	std::string SelectFileWindow::OpenFile(const char* filter)
	{
		// ��ʼ��Dialog���ڣ�ѡ���ļ��Ĵ��ڣ�
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		// memset((Destination),0,(Length))  �����ǵ���
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		//���õ�ǰѡ�ļ�dialog���Ӵ��ڣ��ĸ�������˭������Ȼ�����洰������ HWND==
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 2; //����ڼ�����׺����Ϊ��ѡ��
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}

	std::string SelectFileWindow::SaveFile(const char* filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileNameA(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();

	}


}
