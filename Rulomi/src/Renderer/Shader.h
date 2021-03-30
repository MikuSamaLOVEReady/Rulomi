#pragma once

#include <string>


namespace Rulomi {

	//抽象出接口 refclass 来管理
	class Shader
	{
	public:
		//
		//Shader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);

	};

}