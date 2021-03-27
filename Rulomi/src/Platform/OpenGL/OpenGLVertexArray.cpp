#include "RulomiPch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Rulomi {

	// 用于
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Rulomi::ShaderDataType::Float:    return GL_FLOAT;
		case Rulomi::ShaderDataType::Float2:   return GL_FLOAT;
		case Rulomi::ShaderDataType::Float3:   return GL_FLOAT;
		case Rulomi::ShaderDataType::Float4:   return GL_FLOAT;
		case Rulomi::ShaderDataType::Mat3:     return GL_FLOAT;
		case Rulomi::ShaderDataType::Mat4:     return GL_FLOAT;
		case Rulomi::ShaderDataType::Int:      return GL_INT;
		case Rulomi::ShaderDataType::Int2:     return GL_INT;
		case Rulomi::ShaderDataType::Int3:     return GL_INT;
		case Rulomi::ShaderDataType::Int4:     return GL_INT;
		case Rulomi::ShaderDataType::Bool:     return GL_BOOL;
		}

		RLM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		//绑定VA --->绑定所想要的 VB们 因为可能不止一个 
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		//layout 是 BufferLayout类型 
		//但为啥 这里for就可以 取到 m_Elements 类型
		for (const auto& element : layout.GetElements())
		{
			glEnableVertexAttribArray(index);
			//第一个参数是激活第几种属性ID 
			//第二个参数是这个属性由几个数组成 
			//第三个 这几个数字的类型
			//第四个 normalized 是否开启
			//第五个 stride 表示 每个顶点的总容量大小 （eg 位置坐标3个float 颜色4个float 纹理 3个float 一共10个） 
			// stride 表示将指针向后移动多少个 bytes才能读取下一顶点的数据
			//第五个表示offset 当stride过后，现在这个指针需要向后移动多少个单位才能读取到下一套属性。
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);

			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		//先绑定 VA过后之后的任何bind 都是更具与它来
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
