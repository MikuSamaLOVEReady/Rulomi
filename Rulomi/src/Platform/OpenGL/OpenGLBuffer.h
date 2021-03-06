#pragma once

#include "Renderer/Buffer.h"

namespace Rulomi {

	class OpenGLVertexBuffer: public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, size_t size);
		virtual	~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		//为那种只开辟了GPU空间 但无数据的shader做
		virtual void SetData(const void* data, uint32_t size) override;

	private:
		uint32_t  m_RendererID;
		BufferLayout m_Layout;
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* vertices, uint32_t sizes);
		virtual	~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		inline virtual uint32_t GetCount() const override { return m_Count; };

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};


}


