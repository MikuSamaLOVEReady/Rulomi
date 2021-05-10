#pragma once
#include "RulomiCore/Core.h"
#include "RulomiCore/Log.h"

namespace Rulomi{

	//shader Type
	enum class ShaderDomain
	{
		None = 0, Vertex = 0, Pixel = 1
	};
	
	//每个shader中的uniform有哪些
	class ShaderUniformDeclaration
	{
	private:
		friend class Shader;
		friend class OpenGLShader;
		friend class ShaderStruct;
	public:
		virtual const std::string& GetName() const = 0;
		virtual uint32_t GetSize() const = 0;
		virtual uint32_t GetCount() const = 0;
		virtual uint32_t GetOffset() const = 0;
		virtual ShaderDomain GetDomain() const = 0;
	protected:
		virtual void SetOffset(uint32_t offset) = 0;
	};

	//缓存 shader Uniform
	//class ShaderUniformBufferDeclaration
	//{
	//public:
	//	virtual const std::string& GetName() const = 0;
	//	virtual uint32_t GetRegister() const = 0;
	//	virtual uint32_t GetSize() const = 0;
	//	//缓冲区应该是来提速的。暂时不要
	//	//virtual const ShaderUniformList& GetUniformDeclarations() const = 0;

	//	virtual ShaderUniformDeclaration* FindUniform(const std::string& name) = 0;
	//};


	class ShaderResourceDeclaration
	{
	public:
		virtual const std::string& GetName() const = 0;
		virtual uint32_t GetRegister() const = 0;
		virtual uint32_t GetCount() const = 0;
	};

}