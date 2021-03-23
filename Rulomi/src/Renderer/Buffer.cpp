
#include "RulomiPch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Rulomi {


	VertexBuffer* VertexBuffer::Create(float* vertices, size_t sizes)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    RLM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexBuffer(vertices, sizes);
		}

		RLM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}



	IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t sizes)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    RLM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLIndexBuffer(vertices, sizes);
		}

		RLM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}