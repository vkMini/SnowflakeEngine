#include "sfpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Renderer/OpenGL/OpenGLVertexArray.h"

namespace Snowflake {

	Ref<VertexArray> VertexArray::CreateVertexArray()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create vertex array! No Rendering API was selected!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create vertex array! Unknown Rendering API!");
		return nullptr;
	}

}