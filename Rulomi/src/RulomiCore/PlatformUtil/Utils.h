#pragma once

#include <string>


namespace Rulomi {

	class SelectFileWindow
	{
		//Win32API �ṩwindows�µ� �ļ�����
		public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};


}
