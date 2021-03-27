#pragma once

// renderer 总体流程 begin（） 读取当前场景中的 所有data数据 environment & object itself
// submit 则是提交shader渲染 （数据都准备好了---->提交rendercommand 
//end 
#include "RenderCommand.h"

namespace Rulomi {

	
	class Renderer
	{
	public:
		static void BeginScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray ) ;
		static void EndScene();
		

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		
	};


}


