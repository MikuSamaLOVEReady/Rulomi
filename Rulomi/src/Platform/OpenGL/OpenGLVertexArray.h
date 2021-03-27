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

		// VA 可以作为一个reference 被多个VB链接
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		//VA 这个对象来说如何获取其中的元素
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const {return m_VertexBuffers;}
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		//VB可能有多个
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		//但IB一般只有一个
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};

}


