#pragma once

#include "RendererCore/Texture.h"

namespace Snowflake {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filepath);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind() const override;
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_TextureID;
	};
}