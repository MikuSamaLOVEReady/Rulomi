#include "RulomiPch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Rulomi {

	// ���ڴ� �û��������������� ӳ�䵽 OpenGL���� 
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

		RLM_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		//��VA --->������Ҫ�� VB�� ��Ϊ���ܲ�ֹһ�� 
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		//uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		//layout �� BufferLayout���� 
		//��Ϊɶ ����for�Ϳ��� ȡ�� m_Elements ����
		//for (const auto& element : layout.GetElements())
		//{
		//	glEnableVertexAttribArray(index);
		//	//��һ�������Ǽ���ڼ�������ID 
		//	//�ڶ�����������������ɼ�������� 
		//	//������ �⼸�����ֵ�����
		//	//���ĸ� normalized �Ƿ���
		//	//����� stride ��ʾ ÿ���������������С ��eg λ������3��float ��ɫ4��float ���� 3��float һ��10���� 
		//	// stride ��ʾ��ָ������ƶ����ٸ� bytes���ܶ�ȡ��һ���������
		//	//�������ʾoffset ��stride�����������ָ����Ҫ����ƶ����ٸ���λ���ܶ�ȡ����һ�����ԡ�
		//	glVertexAttribPointer(index,
		//		element.GetComponentCount(),
		//		ShaderDataTypeToOpenGLBaseType(element.Type),
		//		element.Normalized ? GL_TRUE : GL_FALSE,
		//		layout.GetStride(),
		//		(const void*)element.Offset);

		//	index++;
		//}

		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				RLM_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		//�Ȱ� VA����֮����κ�bind ���Ǹ���������
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
