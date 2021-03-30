#include "RulomiPch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rulomi {

	//全局静态场景 只能有一个
	Renderer::SceneData*  Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->VPMatrix = camera.GetVPMatrix();
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		//To Do 如果订好了shader 这里就不用再变化 设置Uniform-->transmission/VP 
		//uniform 每次更新 shader 里面的内容 ----> 
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->VPMatrix);
		//这里开始平移obj
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		//这里就是 renderer 与 render command 链接的地方
		vertexArray->Bind();
		RenderCommand::DrawVertexs(vertexArray);

	}

	void Renderer::EndScene()
	{

	}

}