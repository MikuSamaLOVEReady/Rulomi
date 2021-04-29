#include "RulomiPch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"

namespace Rulomi {

	

	OpenGLShader::OpenGLShader(const std::string& name , const std::string& vertexSource, const std::string& fragmentSource)
		:m_Name(name)
	{
		//// Create an empty vertex shader handle 空的shader容器
		//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		////将 shader内容（source）传递给这个空的容器
		//// Send the vertex shader source code to GL
		//// Note that std::string's .c_str is NULL character terminated.
		//const GLchar* source = vertexSource.c_str();
		//glShaderSource(vertexShader, 1, &source, 0);

		//// Compile the vertex shader
		//glCompileShader(vertexShader);

		//GLint isCompiled = 0;
		//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		////shader 编译报错
		//if (isCompiled == GL_FALSE)
		//{
		//	//记录OpenGL报错信息的长度
		//	GLint maxLength = 0;
		//	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		//	// The maxLength includes the NULL character 创建一个vector来存储错误信息
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
		////第一个参数是shader（一开始是空的） 
		////第二个参数是 我们要写入的string 数量 
		////第三个是 源码string 
		////第四个 给NULL 将自动读取到  第三个参数的 终止符
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

		//	// 如果片段着色器炸了，那之前的vertexshader也没用
		//	glDeleteShader(fragmentShader);
		//	// Either of them. Don't leak shaders.
		//	glDeleteShader(vertexShader);

		//	RLM_CORE_ERROR("{0}", infoLog.data());
		//	RLM_CORE_ASSERT(false, "Fragment shader compilation failure!");
		//	return;
		//}


		//// 编译通过后 将编译后的 shader link进 program
		//m_RendererID = glCreateProgram();
		//GLuint program = m_RendererID;

		//// Attach our shaders to our program
		//glAttachShader(program, vertexShader);
		//glAttachShader(program, fragmentShader);

		//// 将则个GPU着色程序链接到我们 主renderer
		//glLinkProgram(program);

		//// 注意用到的是get progame glGetProgram* instead of glGetShader*.
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

		//// 相当于已经 编译成exe了 你的cpp就不用了
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
		//读取全文
		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		//存储基础default glsl文件 从glsl文件中读取名字
		// assets/src/texture.glsl
		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = filepath.find_last_of(".");
		size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		//收7个
		m_Name = filepath.substr(lastSlash, count);

	}



	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string shaderContents;
		//查一下     opening the file as an input stream  //open for reading + pen in binary mod
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		//calculate size
		if (in)
		{
			// change input stream position by _Off, according to _Way
			in.seekg(0, std::ios::end);
			//tellg 告知到现在位置
			shaderContents.resize(in.tellg());
			//移动光标 到开头
			in.seekg(0, std::ios::beg);

			// count 来读取要存储的字节数
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
		// 位置跳位置
		size_t typeTokenLength = strlen(typeToken);
		//look for "string") beginning at or after _Off 发明会数组这哦那个的index
		//返回所查找字符串的 起始位置
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			//找到行尾
			size_t EndOfLine = source.find_first_of("\r\n", pos);
			//不是行尾才能通过
			RLM_CORE_ASSERT(EndOfLine != std::string::npos, "ERROR not enough file");
			size_t shaderTypeBegin = pos + typeTokenLength + 1;
			//第一个参数是 offset  第二个表示要存储多少个
			std::string type = source.substr(shaderTypeBegin, EndOfLine - shaderTypeBegin);
			//ShaderTypeFromString(type) ---拿到shader类型
			//找到第一个不是 \n\r数据  即下一段起始位置
			size_t nextLinePos = source.find_first_not_of("\r\n", EndOfLine);
			//sahder 标记位置
			pos = source.find(typeToken, nextLinePos);
			// -1 spans len characters (or until the end of the string, whichever comes first).
			//这个函数有问题屮
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos) );
			RLM_CORE_ERROR("AASDAS");
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		//初始容器  size（） 获得的桶的个数 
		//std::vector<GLenum> glshaderIDs(shaderSources.size()); 这个操作是提前添加2个单元
		std::vector<GLenum> glshaderIDs;
		glshaderIDs.reserve(shaderSources.size());

		for (auto& kv : shaderSources)
		{
			//GL_VERTEX_SHADER =这个是个int
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

				// 如果片段着色器炸了，那之前的vertexshader也没用Don't leak shaders.
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

			// 删除程序和shader 所占用空间
			glDeleteProgram(program);
			for (auto id : glshaderIDs)
			{
				glDeleteShader(id);
			}

			RLM_CORE_ERROR("{0}", infoLog.data());
			RLM_CORE_ASSERT(false, "Shader link failure!");
			return;
		} 

		//glDetachShader 解除link关系 如果shader 已经被编译成程序则不需占用资源
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

	// values 具体传递的数值  count 
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

	//用于 更新 uniform 实现动态改变shader的内容
	void OpenGLShader::UploadUniformMat4(const std::string& uniform_name, const glm::mat4& matrix)
	{
		//第一个参数表示在哪个 shader program中
		//第二个是查找 uniform的位置？（我们想要给哪个uniform设置数值）
		GLint location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
		//为这个location上的 unifom设置几个matrix
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}


}