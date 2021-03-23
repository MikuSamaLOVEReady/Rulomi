#pragma once

// ����� Index Buff + Vertex Buffer

namespace Rulomi {
	//Ϊ��ƽ̨���� �����һ������ӿ� û������ �������class�Ľӿ�
	//ֻ���ǹ�����������(
	//���ж������� + VA? 
	class VertexBuffer 
	{
	public:
		virtual	~VertexBuffer(){}

		virtual void Bind()	const	= 0;
		virtual void Unbind()  const  = 0;

		//size_t == unsigned long long 
		static VertexBuffer* Create(float* vertices,  size_t sizes);
	
	};



   //����˳��
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