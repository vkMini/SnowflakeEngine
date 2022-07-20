#include "sfpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

#include <optick.h>

namespace Snowflake {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
	{
		OPTICK_EVENT();

		stbi_set_flip_vertically_on_load(GL_TRUE);

		int width, height, channels;
		stbi_uc* textureData = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

		m_Width = width;
		m_Height = height;

		if (channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}

		SNOWFLAKE_ENGINE_ASSERT(m_InternalFormat & m_DataFormat, "Failed to create OpenGL texture 2D! The internal and/or data format is not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, textureData);

		stbi_image_free(textureData);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		OPTICK_EVENT();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		OPTICK_EVENT();

		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{

		OPTICK_EVENT();
		glBindTextureUnit(slot, m_TextureID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		OPTICK_EVENT();

		uint32_t bytesPerPixel = m_DataFormat == GL_RGBA ? 4 : 3;
		SNOWFLAKE_ENGINE_ASSERT(size == m_Width * m_Height * bytesPerPixel, "Failed to set texture 2D data! It must be the entire texture!");

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

}