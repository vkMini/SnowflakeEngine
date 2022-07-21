#pragma once

#include "RendererCore/Texture.h"

namespace Snowflake {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filepath);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetTextureHandle() const override { return m_TextureID; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_TextureID == ((OpenGLTexture2D&)other).m_TextureID;
		}
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_InternalFormat, m_DataFormat;
		uint32_t m_TextureID;
	};
}