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

		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &chanels, 0);
		// unsigned char = stbi_uc ���û�õ�data �򷵻�null
		RLM_CORE_ASSERT(data, "Invalid path");
		m_Width = width;
		m_Height = height;

		//��������
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		//��������������Ķ������ٿռ���GPU�� ������ �����洢��ʽ


		//���������һ���Ǳ����ĸ�
		//�ڶ���������bitmap ��level �㼶
		//��������������Ҫ�洢�� ��ʽ��8��ʾ ������ͨ��Ϊ8λ��
		//simultaneously specify storage for all levels of a two-dimensional or one-dimensional array texture
		glTextureStorage2D(m_RendererID, 1,GL_RGB8, m_Width, m_Height);

		//OpenGL Ϊ�Զ����� ����Ĵ�С�����minification magnification)
		//��һ��������ʾ���ĸ��������� 
		//�ڶ���ʾ ���������ĸ����� �����ŵ�ʱ��
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//��������֮��Ϳ����ύsubmit�� shader GPU��
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

		//�ͷ�stb ��CPU�Ͽ����ڴ�
		stbi_image_free(data);

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

}