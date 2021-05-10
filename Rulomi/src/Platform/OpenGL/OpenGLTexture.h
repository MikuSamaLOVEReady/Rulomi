#pragma once

#include "Renderer/Texture.h"

#include <glad/glad.h>


namespace Rulomi {

	class OpenGLTexture2D :public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();


		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };
		virtual uint32_t GetRendererID() const override { return m_RendererID; };
		
		//
		virtual void Bind(uint32_t slot = 0) const override;

		virtual void SetData(void* data, uint32_t size) override;
		virtual bool operator==(const Texture& other) const override
		{
			//向下转型一下 必定能转型
			return m_RendererID == ( (OpenGLTexture2D&)other ).m_RendererID;
		}

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height,m_RendererID;
		//opengl 内部存储格式  vs 用户所提供的格式
		GLenum m_InternalFormat, m_DataFormat;
	};



	//3D 的流程和2D流程太不同了！
	class OpenGLTextureCube :public TextureCube
	{
	public:
		OpenGLTextureCube(const std::string& path);
		//OpenGLTextureCube(TextureFormat format, uint32_t width, uint32_t height);
		virtual ~OpenGLTextureCube() =default;
		virtual const std::string& GetPath() const { return NULL; };

		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };
		virtual uint32_t GetRendererID() const override { return m_RenderID; };

			//
		virtual void Bind(uint32_t slot = 0) const override {};

		virtual void SetData(void* data, uint32_t size) override {};
		virtual bool operator==(const Texture& other) const override
		{
			//向下转型一下 必定能转型
			return m_RenderID == ( (OpenGLTextureCube&)other ).m_RenderID;
		}

	private:
		uint32_t m_RenderID;
		std::string m_FilePath;
		unsigned char* m_ImageData;
		TextureFormat m_Format;
		uint32_t m_Width, m_Height;



	};

}



