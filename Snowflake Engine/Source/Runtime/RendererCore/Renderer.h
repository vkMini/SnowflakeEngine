#pragma once

#include "RendererAPI.h"

namespace Snowflake {

	class Renderer
	{
	public:
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
