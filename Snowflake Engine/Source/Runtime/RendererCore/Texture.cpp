#include "sfpch.h"
#include "Texture.h"

#include "Renderer.h"

#include "Renderer/OpenGL/OpenGLTexture.h"

namespace Snowflake {

	Ref<Texture2D> Texture2D::CreateTexture2D(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create texture 2D! No Rendering API was selected!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(filepath);
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create texture 2D! Unknown Rendering API!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::CreateTexture2D(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SNOWFLAKE_ENGINE_ASSERT(false, ""); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create texture 2D! Unknown Rendering API!");
		return nullptr;
	}

}