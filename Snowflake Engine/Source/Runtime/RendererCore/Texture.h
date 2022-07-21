#pragma once

#include "Core/Core.h"

namespace Snowflake {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetTextureHandle() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> CreateTexture2D(const std::string& filepath);
		static Ref<Texture2D> CreateTexture2D(uint32_t width, uint32_t height);
	};
}