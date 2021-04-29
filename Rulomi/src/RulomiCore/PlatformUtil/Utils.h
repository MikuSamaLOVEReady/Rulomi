#pragma once

#include <string>


namespace Rulomi {

	class SelectFileWindow
	{
		//Win32API 提供windows下的 文件窗口
		public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};


}
