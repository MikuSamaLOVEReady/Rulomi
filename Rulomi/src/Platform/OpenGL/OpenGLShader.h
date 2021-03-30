#pragma once

#include "Renderer/Shader.h"
#include "glm/glm.hpp"

namespace Rulomi {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;


		void UploadUniformInt(const std::string& uniform_name, int value);

		void UploadUniformFloat(const std::string& uniform_name, float value);
		void UploadUniformFloat2(const std::string& uniform_name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& uniform_name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& uniform_name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& uniform_name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& uniform_name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;


	};



}



