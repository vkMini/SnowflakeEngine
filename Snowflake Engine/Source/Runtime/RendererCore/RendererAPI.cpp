#include "sfpch.h"
#include "RendererAPI.h"

namespace Snowflake {

	// Use OpenGL as the default rendering API
	RendererAPI::API RendererAPI::s_RendererAPI = API::OpenGL;
}