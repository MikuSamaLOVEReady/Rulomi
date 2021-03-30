#include "RulomiPch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Rulomi {

	Reference<Texture2D> Texture2D::Create(const std::string& path)
	{
			switch (Renderer::GetAPI())
			{
				case RendererAPI::API::None:    RLM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
					//这到底怎么办？ new 还是make_share?
				case RendererAPI::API::OpenGL: std::make_shared<OpenGLTexture2D>(path);
			}

			RLM_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;

	}



}


