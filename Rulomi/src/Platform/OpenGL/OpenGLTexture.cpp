#include "RulomiPch.h"
#include "OpenGLTexture.h"
#include "Renderer/Renderer.h"

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
		//OpenGL 想要的方向 与stb read 文件的方向是相反的
		stbi_set_flip_vertically_on_load(1);

		//第四个参数是啥？
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &chanels, 0);
		// unsigned char = stbi_uc 如果没得到data 则返回null
		RLM_CORE_ASSERT(data, "Invalid path");
		m_Width = width;
		m_Height = height;


		//blending
		//  internalFormat 表图片本身的色彩格式
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

		//创建纹理
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		//将这个创建出来的东西开辟空间在GPU上 三步走 创建存储格式

		//这个函数第一个是保存哪个
		//第二个参数是bitmap 的level 层级
		//第三个是我们想要存储的 格式（8表示 阿尔法通道为8位）
		//simultaneously specify storage for all levels of a two-dimensional or one-dimensional array texture
		// how opengl store data？ 
		glTextureStorage2D(m_RendererID, 1, openGLStoreFormat, m_Width, m_Height);

		//OpenGL 为自动缩放 纹理的大小如果（minification magnification)
		//第一个参数表示对哪个纹理设置 
		//第二表示 是在纹理哪个参数 （缩放的时候）
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//设置完了之后就可以提交submit到 shader GPU上
		// GL_UNSIGNED_BYTE  format of data
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		
		//释放stb 在CPU上开的内存
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
		//只是在GPU上开辟了一部分空间 但并没有设置具体数据--->由setdata动态设置
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

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		RLM_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}


	//天空球
	OpenGLTextureCube::OpenGLTextureCube(const std::string& path)
		: m_FilePath(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(false);

		m_ImageData = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb);
		m_Width = width;
		m_Height = height;
		m_Format = TextureFormat::RGB;

		//将图片分成12份
		uint32_t faceWidth = m_Width / 4;
		uint32_t faceHeight = m_Height / 3;
		RLM_CORE_ASSERT(faceWidth == faceHeight, "Non-square faces!");
		//6个数组存储了些啥？
		std::array<uint8_t*, 6> faces;
		for (size_t i = 0; i < faces.size(); i++)
			faces[i] = new uint8_t[faceWidth * faceHeight * 3]; // 3 BPP


		//将图片切片后存成 faces
		int Index = 0;

		//按列遍历 分成4列 index+4
		for (size_t i = 0; i < 4; i++)
		{
			//每一个子face一行一行赋值
			for (size_t y = 0; y < faceHeight; y++)
			{
				//offset表示在所加载图片上的位置
				size_t yOffset = y + faceHeight;
				for (size_t x = 0; x < faceWidth; x++)
				{
					size_t xOffset = x + i * faceWidth;
					faces[Index][ (x + y * faceWidth) * 3 + 0] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 0];
					faces[Index][ (x + y * faceWidth) * 3 + 1] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 1];
					faces[Index][ (x + y * faceWidth) * 3 + 2] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 2];
				}
			}
			Index++;
		}
		//index +2
		for (size_t i = 0; i < 3; i++)
		{
			// Skip the middle one
			if (i == 1)
				continue;
			for (size_t y = 0; y < faceHeight; y++)
			{
				size_t yOffset = y + i * faceHeight;
				for (size_t x = 0; x < faceWidth; x++)
				{
					size_t xOffset = x + faceWidth;
					faces[Index][(x + y * faceWidth) * 3 + 0] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 0];
					faces[Index][(x + y * faceWidth) * 3 + 1] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 1];
					faces[Index][(x + y * faceWidth) * 3 + 2] = m_ImageData[(xOffset + yOffset * m_Width) * 3 + 2];
				}
			}
			Index++;
		}
		//以上就组成了6面内容
		auto instance = this;

		/*Renderer::Submit([=]() {
			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTextureParameterf(m_RendererID, GL_TEXTURE_MAX_ANISOTROPY, RendererAPI::GetCapabilities().MaxAnisotropy);

			auto format = HazelToOpenGLTextureFormat(m_Format);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[2]);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[0]);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[4]);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[5]);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[1]);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[3]);

			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

			glBindTexture(GL_TEXTURE_2D, 0);

			for (size_t i = 0; i < faces.size(); i++)
				delete[] faces[i];

			stbi_image_free(m_ImageData);
			});*/


	}

	//OpenGLTextureCube::OpenGLTextureCube(TextureFormat format, uint32_t width, uint32_t height)

	//}

}