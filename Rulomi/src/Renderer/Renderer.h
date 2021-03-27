#pragma once

// renderer �������� begin���� ��ȡ��ǰ�����е� ����data���� environment & object itself
// submit �����ύshader��Ⱦ �����ݶ�׼������---->�ύrendercommand 
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


