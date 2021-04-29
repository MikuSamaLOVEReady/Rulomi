#include "RulomiPch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"

namespace Rulomi {

	

	OpenGLShader::OpenGLShader(const std::string& name , const std::string& vertexSource, const std::string& fragmentSource)
		:m_Name(name)
	{
		//// Create an empty vertex shader handle �յ�shader����
		//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		////�� shader���ݣ�source�����ݸ�����յ�����
		//// Send the vertex shader source code to GL
		//// Note that std::string's .c_str is NULL character terminated.
		//const GLchar* source = vertexSource.c_str();
		//glShaderSource(vertexShader, 1, &source, 0);

		//// Compile the vertex shader
		//glCompileShader(vertexShader);

		//GLint isCompiled = 0;
		//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		////shader ���뱨��
		//if (isCompiled == GL_FALSE)
		//{
		//	//��¼OpenGL������Ϣ�ĳ���
		//	GLint maxLength = 0;
		//	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		//	// The maxLength includes the NULL character ����һ��vector���洢������Ϣ
		//	std::vector<GLchar> infoLog(maxLength);
		//	glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		//	// We don't need the shader anymore.
		//	glDeleteShader(vertexShader);


		//	RLM_CORE_ERROR("{0}", infoLog.data());
		//	RLM_CORE_ASSERT(false, "Vertex shader compilation failure!");

		//	return;
		//}

		//// Create an empty fragment shader handle
		//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//// Send the fragment shader source code to GL
		//// Note that std::string's .c_str is NULL character terminated.
		//source = fragmentSource.c_str();
		////��һ��������shader��һ��ʼ�ǿյģ� 
		////�ڶ��������� ����Ҫд���string ���� 
		////�������� Դ��string 
		////���ĸ� ��NULL ���Զ���ȡ��  ������������ ��ֹ��
		//glShaderSource(fragmentShader, 1, &source, 0);

		//// Compile the fragment shader
		//glCompileShader(fragmentShader);

		//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		//if (isCompiled == GL_FALSE)
		//{
		//	GLint maxLength = 0;
		//	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		//	// The maxLength includes the NULL character
		//	std::vector<GLchar> infoLog(maxLength);
		//	glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		//	// ���Ƭ����ɫ��ը�ˣ���֮ǰ��vertexshaderҲû��
		//	glDeleteShader(fragmentShader);
		//	// Either of them. Don't leak shaders.
		//	glDeleteShader(vertexShader);

		//	RLM_CORE_ERROR("{0}", infoLog.data());
		//	RLM_CORE_ASSERT(false, "Fragment shader compilation failure!");
		//	return;
		//}


		//// ����ͨ���� �������� shader link�� program
		//m_RendererID = glCreateProgram();
		//GLuint program = m_RendererID;

		//// Attach our shaders to our program
		//glAttachShader(program, vertexShader);
		//glAttachShader(program, fragmentShader);

		//// �����GPU��ɫ�������ӵ����� ��renderer
		//glLinkProgram(program);

		//// ע���õ�����get progame glGetProgram* instead of glGetShader*.
		//GLint isLinked = 0;
		//glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		//if (isLinked == GL_FALSE)
		//{
		//	GLint maxLength = 0;
		//	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//	// The maxLength includes the NULL character
		//	std::vector<GLchar> infoLog(maxLength);
		//	glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		//	// We don't need the program anymore.
		//	glDeleteProgram(program);
		//	// Don't leak shaders either.
		//	glDeleteShader(vertexShader);
		//	glDeleteShader(fragmentShader);

		//	RLM_CORE_ERROR("{0}", infoLog.data());
		//	RLM_CORE_ASSERT(false, "Shader link failure!");
		//	return;
		//}

		//// �൱���Ѿ� �����exe�� ���cpp�Ͳ�����
		//glDetachShader(program, vertexShader);
		//glDetachShader(program, fragmentShader);
		
		//on stack
		std::unordered_map<GLenum, std::string> sourcesFile;
		sourcesFile[GL_VERTEX_SHADER] = vertexSource;
		sourcesFile[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sourcesFile);


	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		//��ȡȫ��
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		//�洢����default glsl�ļ� ��glsl�ļ��ж�ȡ����
		// assets/src/texture.glsl
		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = filepath.find_last_of(".");
		size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		//��7��
		m_Name = filepath.substr(lastSlash, count);

	}



	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string shaderContents;
		//��һ��     opening the file as an input stream  //open for reading + pen in binary mod
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		//calculate size
		if (in)
		{
			// change input stream position by _Off, according to _Way
			in.seekg(0, std::ios::end);
			//tellg ��֪������λ��
			shaderContents.resize(in.tellg());
			//�ƶ���� ����ͷ
			in.seekg(0, std::ios::beg);

			// count ����ȡҪ�洢���ֽ���
			in.read(&shaderContents[0], shaderContents.size());
			in.close();
		}
		else
		{
			RLM_CORE_ERROR("file can not open {0}", filepath);
		}
		return shaderContents;
	}

	static GLenum ShaderTypeFromString(std::string ShaderName)
	{
		if (ShaderName == "vertex")
			return GL_VERTEX_SHADER;
		if (ShaderName == "fragment" )
			return GL_FRAGMENT_SHADER;


		RLM_CORE_ASSERT(false, "invalid shader type");
		return 0;

	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		// key value pair
		// GLenum = shader type  //  std::string shader contents
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		// λ����λ��
		size_t typeTokenLength = strlen(typeToken);
		//look for "string") beginning at or after _Off ������������Ŷ�Ǹ���index
		//�����������ַ����� ��ʼλ��
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			//�ҵ���β
			size_t EndOfLine = source.find_first_of("\r\n", pos);
			//������β����ͨ��
			RLM_CORE_ASSERT(EndOfLine != std::string::npos, "ERROR not enough file");
			size_t shaderTypeBegin = pos + typeTokenLength + 1;
			//��һ�������� offset  �ڶ�����ʾҪ�洢���ٸ�
			std::string type = source.substr(shaderTypeBegin, EndOfLine - shaderTypeBegin);
			//ShaderTypeFromString(type) ---�õ�shader����
			//�ҵ���һ������ \n\r����  ����һ����ʼλ��
			size_t nextLinePos = source.find_first_not_of("\r\n", EndOfLine);
			//sahder ���λ��
			pos = source.find(typeToken, nextLinePos);
			// -1 spans len characters (or until the end of the string, whichever comes first).
			//���������������
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos) );
			RLM_CORE_ERROR("AASDAS");
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		//��ʼ����  size���� ��õ�Ͱ�ĸ��� 
		//std::vector<GLenum> glshaderIDs(shaderSources.size()); �����������ǰ���2����Ԫ
		std::vector<GLenum> glshaderIDs;
		glshaderIDs.reserve(shaderSources.size());

		for (auto& kv : shaderSources)
		{
			//GL_VERTEX_SHADER =����Ǹ�int
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);
			const GLchar* sourceString = source.c_str();
			glShaderSource(shader, 1, &sourceString, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// ���Ƭ����ɫ��ը�ˣ���֮ǰ��vertexshaderҲû��Don't leak shaders.
				glDeleteShader(shader);

				RLM_CORE_ERROR("{0}", infoLog.data());
				RLM_CORE_ASSERT(false, "Fragment shader compilation failure!");
				break;
			}
			glAttachShader(program, shader);
			glshaderIDs.push_back(shader);
		}

		//finish compiling
		m_RendererID = program;
		// Link our program
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

			// ɾ�������shader ��ռ�ÿռ�
			glDeleteProgram(program);
			for (auto id : glshaderIDs)
			{
				glDeleteShader(id);
			}

			RLM_CORE_ERROR("{0}", infoLog.data());
			RLM_CORE_ASSERT(false, "Shader link failure!");
			return;
		} 

		//glDetachShader ���link��ϵ ���shader �Ѿ�������ɳ�������ռ����Դ
		for (auto id : glshaderIDs)
			glDetachShader(program, id);

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

	// values ���崫�ݵ���ֵ  count 
	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		//upload
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
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

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}


}