#include "RulomiPch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"
namespace Rulomi {

	/////////////////////////////////////////////////////
	////////////////VertexBuffer///////////////////////
	/////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size)
	{
		glCreateBuffers(1,&m_RendererID);   //二合一 //Vertex Array glGenVertexArrays(1, &m_VertexArray); 	glBindVertexArray(m_VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		//将数据传递给GPU
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1 , &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		//第二个参数为啥不是 vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	/////////////////////////////////////////////////////
	////////////////IndexBuffer///////////////////////
	/////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* vertices, uint32_t count)
		:m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);   //二合一 //Vertex Array glGenVertexArrays(1, &m_VertexArray); 	glBindVertexArray(m_VertexArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	  //将数据传递给GPU
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t) , vertices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1,&m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0 );
	}

	

}