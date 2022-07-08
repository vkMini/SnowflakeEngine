#pragma once

#include "RendererCore/RendererContext.h"

namespace Snowflake {

	class OpenGLContext : public RendererContext
	{
	public:
		OpenGLContext(void* windowHandle);
		
		virtual void Initialize() override;
	private:
		void* m_WindowHandle;
	};
}