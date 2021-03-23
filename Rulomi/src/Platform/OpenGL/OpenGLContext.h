#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;//forward decleartion

namespace Rulomi {

	class OpenGLContext: public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;

	};



}


