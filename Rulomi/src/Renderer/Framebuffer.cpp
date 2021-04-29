#include "RulomiPch.h"
#include "Framebuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"


namespace Rulomi {

	Reference<Framebuffer> Framebuffer::Create(FramebufferSpecification& specifiaction)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    RLM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLFramebuffer>(specifiaction);
		}

		RLM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

		return Reference<Framebuffer>();
	}

}