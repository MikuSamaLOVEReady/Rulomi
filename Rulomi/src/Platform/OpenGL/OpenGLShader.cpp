#include "RulomiPch.h"
#include "OpenGLShader.h"


#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"

namespace Rulomi {

	
	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		// Create an empty vertex shader handle �յ�shader����
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//�� shader���ݣ�source�����ݸ�����յ�����
		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		//shader ���뱨��
		if (isCompiled == GL_FALSE)
		{
			//��¼OpenGL������Ϣ�ĳ���
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character ����һ��vector���洢������Ϣ
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
		//��һ��������shader��һ��ʼ�ǿյģ� 
		//�ڶ��������� ����Ҫд���string ���� 
		//�������� Դ��string 
		//���ĸ� ��NULL ���Զ���ȡ��  ������������ ��ֹ��
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

			// ���Ƭ����ɫ��ը�ˣ���֮ǰ��vertexshaderҲû��
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			RLM_CORE_ERROR("{0}", infoLog.data());
			RLM_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}


		// ����ͨ���� �������� shader link�� program
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// �����GPU��ɫ�������ӵ����� ��renderer
		glLinkProgram(program);

		// ע���õ�����get progame glGetProgram* instead of glGetShader*.
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

		// �൱���Ѿ� �����exe�� ���cpp�Ͳ�����
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

	//���� ���� uniform ʵ�ֶ�̬�ı�shader������
	void OpenGLShader::UploadUniformMat4(const std::string& uniform_name, const glm::mat4& matrix)
	{
		//��һ��������ʾ���ĸ� shader program��
		//�ڶ����ǲ��� uniform��λ�ã���������Ҫ���ĸ�uniform������ֵ��
		GLint location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
		//Ϊ���location�ϵ� unifom���ü���matrix
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}