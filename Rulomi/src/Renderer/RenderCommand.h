#pragma once


// RenderCommand 功能类似 一个wrapper *（将renderer的需求分发给对应的平台的API)
//这也可以直接调用
//它要想调用 RendererAPI 的话 则需要有一个这东西
#include "RendererAPI.h"

namespace Rulomi {

	class RenderCommand
	{
	public:
		inline static void init()
		{
			s_RendererAPI->init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void DrawIndexed(const Reference<VertexArray>& vertexArray, uint32_t count = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}

		//将 shader绘制命令传递给 具体的API处理
		inline static void DrawVertexs(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawVertexs(vertexArray);
		}
	private:
		//不提供构造， 所有Render command 都可共用这一个
		static RendererAPI* s_RendererAPI;
	};


}



