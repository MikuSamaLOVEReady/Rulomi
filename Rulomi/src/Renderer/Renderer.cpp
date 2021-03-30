#include "RulomiPch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rulomi {

	//ȫ�־�̬���� ֻ����һ��
	Renderer::SceneData*  Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->VPMatrix = camera.GetVPMatrix();
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		//To Do ���������shader ����Ͳ����ٱ仯 ����Uniform-->transmission/VP 
		//uniform ÿ�θ��� shader ��������� ----> 
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->VPMatrix);
		//���￪ʼƽ��obj
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		//������� renderer �� render command ���ӵĵط�
		vertexArray->Bind();
		RenderCommand::DrawVertexs(vertexArray);

	}

	void Renderer::EndScene()
	{

	}

}