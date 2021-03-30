#pragma once

#include <string>


namespace Rulomi {

	//������ӿ� refclass ������
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