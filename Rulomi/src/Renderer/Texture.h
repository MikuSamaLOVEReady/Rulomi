#pragma once

#include <string>
#include "RulomiCore/Core.h"

namespace Rulomi {

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




}

