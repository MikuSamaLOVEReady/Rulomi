#include "RulomiPch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include "stb_image.h"



namespace Rulomi {

	//
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{

		//һ�������� �ļ�·��
		//��2��3���� output �����������ȡ���� ����ĳ���
		//������ ��ͼƬ����Ϣͨ�� RGBA�����ĸ�����Ҫ��ͨ��
		int width, height, chanels;
		//OpenGL ��Ҫ�ķ��� ��stb read �ļ��ķ������෴��
		stbi_set_flip_vertically_on_load(1);

		//���ĸ�������ɶ��
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &chanels, 0);
		// unsigned char = stbi_uc ���û�õ�data �򷵻�null
		RLM_CORE_ASSERT(data, "Invalid path");
		m_Width = width;
		m_Height = height;


		//blending
		//  internalFormat ��ͼƬ�����ɫ�ʸ�ʽ
		//  dataFormat      
		GLenum openGLStoreFormat = 0, dataFormat = 0;

		if (chanels == 4)
		{
			openGLStoreFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (chanels == 3)
		{
			openGLStoreFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = openGLStoreFormat;
		m_DataFormat = dataFormat;

		RLM_CORE_ASSERT(openGLStoreFormat & dataFormat, "empty channel")

		//��������
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		//��������������Ķ������ٿռ���GPU�� ������ �����洢��ʽ

		//���������һ���Ǳ����ĸ�
		//�ڶ���������bitmap ��level �㼶
		//��������������Ҫ�洢�� ��ʽ��8��ʾ ������ͨ��Ϊ8λ��
		//simultaneously specify storage for all levels of a two-dimensional or one-dimensional array texture
		// how opengl store data�� 
		glTextureStorage2D(m_RendererID, 1, openGLStoreFormat, m_Width, m_Height);

		//OpenGL Ϊ�Զ����� ����Ĵ�С�����minification magnification)
		//��һ��������ʾ���ĸ��������� 
		//�ڶ���ʾ ���������ĸ����� �����ŵ�ʱ��
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//��������֮��Ϳ����ύsubmit�� shader GPU��
		// GL_UNSIGNED_BYTE  format of data
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		
		//�ͷ�stb ��CPU�Ͽ����ڴ�
		stbi_image_free(data);

	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		:m_Width(width),m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//ֻ����GPU�Ͽ�����һ���ֿռ� ����û�����þ�������--->��setdata��̬����
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		// �����Ӧ�������λ��bind  ������ʱ�����Ǵ����slot ����
		// ��ʱ�� ��shader ���õ���ֹһ�� texture
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		RLM_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}




}