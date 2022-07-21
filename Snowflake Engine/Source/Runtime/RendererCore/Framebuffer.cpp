#include "sfpch.h"
#include "Framebuffer.h"

#include "Renderer.h"

#include "Renderer/OpenGL/OpenGLFramebuffer.h"

namespace Snowflake {

	Ref<Framebuffer> Framebuffer::CreateFramebuffer(const FramebufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create framebuffer! No Rendering API was selected!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(specification);
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create framebuffer! Unknown Rendering API!");
		return nullptr;
	}

}