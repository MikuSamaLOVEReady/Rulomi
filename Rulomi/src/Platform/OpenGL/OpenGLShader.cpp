#include "RulomiPch.h"
#include "OpenGLShader.h"


#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"

namespace Rulomi {

	
	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		// Create an empty vertex shader handle 空的shader容器
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//将 shader内容（source）传递给这个空的容器
		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		//shader 编译报错
		if (isCompiled == GL_FALSE)
		{
			//记录OpenGL报错信息的长度
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character 创建一个vector来存储错误信息
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);


			RLM_CORE_ERROR("{0}", infoLog.data());
			RLM_CORE_ASSERT(false, "Vertex shader compilation failure!");

			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSource.c_str();
		//第一个参数是shader（一开始是空的） 
		//第二个参数是 我们要写入的string 数量 
		//第三个是 源码string 
		//第四个 给NULL 将自动读取到  第三个参数的 终止符
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// 如果片段着色器炸了，那之前的vertexshader也没用
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			RLM_CORE_ERROR("{0}", infoLog.data());
			RLM_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}


		// 编译通过后 将编译后的 shader link进 program
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// 将则个GPU着色程序链接到我们 主renderer
		glLinkProgram(program);

		// 注意用到的是get progame glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			RLM_CORE_ERROR("{0}", infoLog.data());
			RLM_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// 相当于已经 编译成exe了 你的cpp就不用了
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& uniform_name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& uniform_name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& uniform_name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& uniform_name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& uniform_name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& uniform_name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	//用于 更新 uniform 实现动态改变shader的内容
	void OpenGLShader::UploadUniformMat4(const std::string& uniform_name, const glm::mat4& matrix)
	{
		//第一个参数表示在哪个 shader program中
		//第二个是查找 uniform的位置？（我们想要给哪个uniform设置数值）
		GLint location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
		//为这个location上的 unifom设置几个matrix
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}