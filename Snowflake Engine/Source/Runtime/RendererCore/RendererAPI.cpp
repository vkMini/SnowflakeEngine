#include "sfpch.h"
#include "RendererAPI.h"

#include "Renderer.h"

#include "Renderer/OpenGL/OpenGLRendererAPI.h"

namespace Snowflake {


	RendererAPI::API RendererAPI::s_RendererAPI = API::OpenGL;

	Scope<RendererAPI> RendererAPI::CreateAPI()
	{
		switch (Renderer::GetAPI())
		{
			case API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create Rendering API instance! Unknown Rendering API!");
		return nullptr;
	}
}