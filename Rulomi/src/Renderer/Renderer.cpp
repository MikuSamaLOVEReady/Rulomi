#include "RulomiPch.h"
#include "Renderer.h"


namespace Rulomi {

	void Renderer::BeginScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		//������� renderer �� render command ���ӵĵط�
		vertexArray->Bind();
		RenderCommand::DrawVertexs(vertexArray);

	}

	void Renderer::EndScene()
	{

	}

}