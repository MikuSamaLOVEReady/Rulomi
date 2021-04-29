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

	//添加已有shader 到缓存
	void ShaderLibrary::Add(const Reference<Shader>& shader)
	{
		//表示使用 默认shader名 = 文件民
		std::string shaderName = shader->GetName();
		RLM_CORE_ASSERT(!ShaderCashed(shaderName), "Has already exist shader");
		m_Shaders[shaderName] = shader;
	}

	void ShaderLibrary::Add(const std::string customizedName, const Reference<Shader>& shader)
	{
		//表示使用 默认shader名 = 文件民
		RLM_CORE_ASSERT(!ShaderCashed(customizedName), "Has already exist shader");
		m_Shaders[customizedName] = shader;
	}

	//根据glsl文件创建新shader 到缓存
	Reference<Shader> ShaderLibrary::Load(const std::string& path)
	{
		//创建
		Reference<Shader> shader = Shader::Create(path);
		//添加缓存
		Add(shader);
		return shader;
	}

	//自定义名称
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