#pragma once

#include <string>
#include "RulomiCore/Core.h"

namespace Rulomi {

	enum class TextureFormat
	{
		None = 0,
		RGB = 1,
		RGBA = 2,
		Float16 = 3
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;


		//参数时槽位
		virtual void Bind(uint32_t slot = 0) const = 0;

		//补充的新的方法？主要干啥？
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Reference<Texture2D> Create(const std::string& path);
		static Reference<Texture2D> Create(uint32_t width, uint32_t height);
	};

	//天空球纹理
	class TextureCube : public Texture
	{
	public:
		static Reference<TextureCube> Create(TextureFormat format, uint32_t width, uint32_t height);
		static Reference<TextureCube> Create(const std::string& path);

		//virtual const std::string& GetPath() const = 0;
	};



}

