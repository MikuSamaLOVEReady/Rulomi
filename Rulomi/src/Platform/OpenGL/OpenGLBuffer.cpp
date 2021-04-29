#include "RulomiPch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"
namespace Rulomi {

	/////////////////////////////////////////////////////
	////////////////VertexBuffer///////////////////////
	/////////////////////////////////////////////////////

	//ֻ��GPU�Ͽ����˿ռ䣬��û�о�������
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	/*void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}*/

	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size)
	{
		glCreateBuffers(1,&m_RendererID);   //����һ //Vertex Array glGenVertexArrays(1, &m_VertexArray); 	glBindVertexArray(m_VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		//�����ݴ��ݸ�GPU
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	}

	

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1 , &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		//�ڶ�������Ϊɶ���� vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}


	/////////////////////////////////////////////////////
	////////////////IndexBuffer///////////////////////
	/////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* vertices, uint32_t count)
		:m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);   //����һ //Vertex Array glGenVertexArrays(1, &m_VertexArray); 	glBindVertexArray(m_VertexArray);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	  //�����ݴ��ݸ�GPU
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