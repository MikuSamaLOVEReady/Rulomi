#pragma once

// 抽象层 Index Buff + Vertex Buffer

namespace Rulomi {
	//为了平台独立 这个是一个抽象接口 没有数据 构造这个class的接口
	//只能是构造他的子类(
	//所有顶点数据 + VA? 
	class VertexBuffer 
	{
	public:
		virtual	~VertexBuffer(){}

		virtual void Bind()	const	= 0;
		virtual void Unbind()  const  = 0;

		//size_t == unsigned long long 
		static VertexBuffer* Create(float* vertices,  size_t sizes);
	
	};



   //绘制顺序
	class IndexBuffer 
	{
	public:
		virtual	~IndexBuffer() {}

		virtual void Bind()  const = 0;
		virtual void Unbind() const  = 0;
		 
		virtual uint32_t GetCount() const = 0;
		//size_t == unsigned long long 
		// uint32_t == unsigned int 
		static IndexBuffer* Create(uint32_t* vertices, uint32_t sizes);

	};


}