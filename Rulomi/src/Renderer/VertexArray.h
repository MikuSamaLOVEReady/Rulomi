#pragma once

#include <memory>
#include "Renderer/Buffer.h"

namespace Rulomi {


	//ͬ��Ҳ�ǽӿ�����
	class VertexArray
	{
	public:
		virtual  ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// VA ������Ϊһ��reference �����VB����
		virtual void AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Reference<IndexBuffer>& indexBuffer) = 0;


		//VA ���������˵��λ�ȡ���е�Ԫ��
		virtual const std::vector<Reference<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const = 0;

		static Reference<VertexArray>Create();
	};



}