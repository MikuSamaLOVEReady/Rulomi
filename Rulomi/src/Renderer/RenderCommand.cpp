#include "RulomiPch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Rulomi {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}