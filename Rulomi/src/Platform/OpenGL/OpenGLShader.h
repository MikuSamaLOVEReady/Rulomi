#pragma once

#include "Renderer/Shader.h"
#include "glm/glm.hpp"


typedef unsigned int GLenum;

namespace Rulomi {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		OpenGLShader(const std::string& filepath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		inline virtual const std::string& GetName() const override { return m_Name; }

		//其实是upload uniform本质上
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		////// 为shader 动态设置参数 By uniform
		void UploadUniformInt(const std::string& uniform_name, int value);

		void UploadUniformFloat(const std::string& uniform_name, float value);
		void UploadUniformFloat2(const std::string& uniform_name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& uniform_name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& uniform_name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& uniform_name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& uniform_name, const glm::mat4& matrix);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);


	private:
		//
		std::string ReadFile(const std::string& filepath);
		//hashMap 存储shader class
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;

	};



}



