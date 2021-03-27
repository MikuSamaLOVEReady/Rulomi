#include "RulomiPch.h"
#include "RendererAPI.h"


namespace Rulomi {
	//(单例的类型) 变量类型             被赋值的变量名称    =     所给数值
	RendererAPI::API   RendererAPI::s_API = RendererAPI::API::OpenGL;

}