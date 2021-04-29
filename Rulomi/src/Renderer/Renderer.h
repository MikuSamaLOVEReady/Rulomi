#pragma once

// renderer 总体流程 begin（） 读取当前场景中的 所有data数据 environment & object itself
// submit 则是提交shader渲染 （数据都准备好了---->提交rendercommand 
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
		//submit 需要知道当前绑定哪个shader 
		static void Submit(const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertexArray, 
			const glm::mat4& transform = glm::mat4(1.0f) );
		static void EndScene();
		

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		// DNF: 相机所需要的场景data的初始化
		// environment + 相机自身
		struct SceneData
		{
			//摄像机 view * project matix
			glm::mat4 VPMatrix;
		};
		
		static SceneData* m_SceneData;

		
	};


}


