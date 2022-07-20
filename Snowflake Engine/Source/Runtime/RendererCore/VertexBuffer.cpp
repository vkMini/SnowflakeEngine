#include "sfpch.h"
#include "VertexBuffer.h"

#include "Renderer.h"

#include "Renderer/OpenGL/OpenGLVertexBuffer.h"

namespace Snowflake {

	Ref<VertexBuffer> VertexBuffer::CreateBuffer(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create vertex buffer! No Rendering API was selected!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create vertex buffer! Unknown Rendering API!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::CreateBuffer(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create vertex buffer! No Rendering API was selected!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create vertex buffer! Unknown Rendering API!");
		return nullptr;
	}

}