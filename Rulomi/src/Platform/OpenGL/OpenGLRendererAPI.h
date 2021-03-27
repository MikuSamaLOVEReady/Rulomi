#pragma once

#include "Renderer/RendererAPI.h"


namespace Rulomi {

	class OpenGLRendererAPI: public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawVertexs(const std::shared_ptr<VertexArray>& vertexArray) override;
	};


}

