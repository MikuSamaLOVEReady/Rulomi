#include "RulomiPch.h"
#include "Renderer.h"


namespace Rulomi {

	void Renderer::BeginScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		//这里就是 renderer 与 render command 链接的地方
		vertexArray->Bind();
		RenderCommand::DrawVertexs(vertexArray);

	}

	void Renderer::EndScene()
	{

	}

}