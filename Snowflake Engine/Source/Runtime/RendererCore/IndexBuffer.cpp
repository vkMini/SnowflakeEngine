#include "sfpch.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#include "Renderer/OpenGL/OpenGLIndexBuffer.h"

namespace Snowflake {

	Ref<IndexBuffer> IndexBuffer::CreateBuffer(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create index buffer! No Rendering API was selected!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create index buffer! Unknown Rendering API!");
		return nullptr;
	}

}