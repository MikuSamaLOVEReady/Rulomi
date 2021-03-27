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

		// VA ������Ϊһ��reference �����VB����
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		//VA ���������˵��λ�ȡ���е�Ԫ��
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const {return m_VertexBuffers;}
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		//VB�����ж��
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		//��IBһ��ֻ��һ��
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};

}


