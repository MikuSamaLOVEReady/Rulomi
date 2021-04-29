#include "RulomiPch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Rulomi {

	Reference<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    RLM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>( name, vertexSource, fragmentSource) ;
		}

		RLM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

	Reference<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    RLM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return  std::make_shared<OpenGLShader>(path);
		}
		RLM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	//�������shader ������
	void ShaderLibrary::Add(const Reference<Shader>& shader)
	{
		//��ʾʹ�� Ĭ��shader�� = �ļ���
		std::string shaderName = shader->GetName();
		RLM_CORE_ASSERT(!ShaderCashed(shaderName), "Has already exist shader");
		m_Shaders[shaderName] = shader;
	}

	void ShaderLibrary::Add(const std::string customizedName, const Reference<Shader>& shader)
	{
		//��ʾʹ�� Ĭ��shader�� = �ļ���
		RLM_CORE_ASSERT(!ShaderCashed(customizedName), "Has already exist shader");
		m_Shaders[customizedName] = shader;
	}

	//����glsl�ļ�������shader ������
	Reference<Shader> ShaderLibrary::Load(const std::string& path)
	{
		//����
		Reference<Shader> shader = Shader::Create(path);
		//��ӻ���
		Add(shader);
		return shader;
	}

	//�Զ�������
	Reference<Shader> ShaderLibrary::Load(const std::string& shaderName, const std::string& path)
	{
		Reference<Shader> shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	Reference<Shader> ShaderLibrary::GetShaderByName(const std::string& name)
	{
		RLM_CORE_ASSERT(ShaderCashed(name), " shader not cashed");
		Reference<Shader> shader = m_Shaders[name];
		return shader;
	}

	bool ShaderLibrary::ShaderCashed(const std::string& shaderName) const
	{
		return m_Shaders.find(shaderName)!= m_Shaders.end();
	}

	

}