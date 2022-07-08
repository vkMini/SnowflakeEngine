#pragma once

#include "Core/Core.h"

namespace Snowflake {

	class RendererContext
	{
	public:
		virtual void Initialize() = 0;
		
		static Scope<RendererContext> CreateContext(void* windowHandle);
	};
}