#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "Renderer/ShaderUniform.h"

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

		//当然 shaderID 也可唯一识别          用名字---暂时不解决hash 冲突
		virtual const std::string& GetName() const = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		static Reference<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		static Reference<Shader> Create(const std::string& path);

	};


	//提供一些cashed shader
	class ShaderLibrary
	{
	public:
		//在chashed shader中添加 新cashed shader
		void Add(const Reference<Shader>& shader);
		void Add(const std::string customizedName ,const Reference<Shader>& shader);

		//load 表示还没有已经编译好的shader
		//需要从glsl 创建 -> 缓存 ->返回
		Reference<Shader> Load(const std::string& path);
		//可以 自定义缓存shader的名字
		Reference<Shader> Load(const std::string& shaderName, const std::string& path);
		// 从缓存中获取shader
		Reference<Shader> GetShaderByName(const std::string& name);

		bool ShaderCashed(const std::string& shaderName) const;

	private:
		//名称 + 指向预设shader的指针
		std::unordered_map < std::string, Reference<Shader> > m_Shaders;


	};


}