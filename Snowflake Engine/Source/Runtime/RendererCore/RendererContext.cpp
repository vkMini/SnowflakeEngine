#include "sfpch.h"
#include "RendererContext.h"

#include "Renderer/OpenGL/OpenGLContext.h"

#include "Renderer.h"

namespace Snowflake {

	Scope<RendererContext> RendererContext::CreateContext(void* windowHandle)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create renderer context! No Rendering API was selected!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(windowHandle);
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create renderer context! Unknown Rendering API!");
		return nullptr;
	}

}