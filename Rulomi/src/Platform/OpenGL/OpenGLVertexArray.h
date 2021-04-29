#pragma once
#include "Renderer/VertexArray.h"

namespace Rulomi {

	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual  ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		// VA ������Ϊһ��reference �����VB����  Add��ͬʱҲset
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		//VA ���������˵��λ�ȡ���е�Ԫ��
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const {return m_VertexBuffers;}
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		//VB�����ж��
		std::vector<Reference<VertexBuffer>> m_VertexBuffers;
		//��IBһ��ֻ��һ��
		Reference<IndexBuffer> m_IndexBuffer;

	};

}


