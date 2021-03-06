#pragma once

#include <memory>
#include "Renderer/Buffer.h"

namespace Rulomi {


	//同样也是接口类型
	class VertexArray
	{
	public:
		virtual  ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// VA 可以作为一个reference 被多个VB链接
		virtual void AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Reference<IndexBuffer>& indexBuffer) = 0;


		//VA 这个对象来说如何获取其中的元素
		virtual const std::vector<Reference<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const = 0;

		static Reference<VertexArray>Create();
	};



}