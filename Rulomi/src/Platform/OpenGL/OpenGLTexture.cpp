#include "RulomiPch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include "stb_image.h"



namespace Rulomi {

	//
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{

		//一个参数是 文件路径
		//第2，3个是 output 即这个函数读取到的 纹理的长宽
		//第三个 是图片的信息通道 RGBA　第四个是想要的通道
		int width, height, chanels;

		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &chanels, 0);
		// unsigned char = stbi_uc 如果没得到data 则返回null
		RLM_CORE_ASSERT(data, "Invalid path");
		m_Width = width;
		m_Height = height;

		//创建纹理
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		//将这个创建出来的东西开辟空间在GPU上 三步走 创建存储格式


		//这个函数第一个是保存哪个
		//第二个参数是bitmap 的level 层级
		//第三个是我们想要存储的 格式（8表示 阿尔法通道为8位）
		//simultaneously specify storage for all levels of a two-dimensional or one-dimensional array texture
		glTextureStorage2D(m_RendererID, 1,GL_RGB8, m_Width, m_Height);

		//OpenGL 为自动缩放 纹理的大小如果（minification magnification)
		//第一个参数表示对哪个纹理设置 
		//第二表示 是在纹理哪个参数 （缩放的时候）
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//设置完了之后就可以提交submit到 shader GPU上
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

		//释放stb 在CPU上开的内存
		stbi_image_free(data);

	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		// 在相对应的纹理槽位上bind  采样的时候则是从这个slot 来找
		// 有时候 在shader 中用到不止一个 texture
		glBindTextureUnit(slot, m_RendererID);
	}

}