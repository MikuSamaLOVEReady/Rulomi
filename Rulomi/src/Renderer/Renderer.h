#pragma once

// renderer �������� begin���� ��ȡ��ǰ�����е� ����data���� environment & object itself
// submit �����ύshader��Ⱦ �����ݶ�׼������---->�ύrendercommand 
//end 
#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Camera.h"
#include "Shader.h"

namespace Rulomi {

	
	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void BeginScene(Camera& camera, glm::mat4& transform);
		//submit ��Ҫ֪����ǰ���ĸ�shader 
		static void Submit(const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertexArray, 
			const glm::mat4& transform = glm::mat4(1.0f) );
		static void EndScene();
		

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		// DNF: �������Ҫ�ĳ���data�ĳ�ʼ��
		// environment + �������
		struct SceneData
		{
			//����� view * project matix
			glm::mat4 VPMatrix;
		};
		
		static SceneData* m_SceneData;

		
	};


}


