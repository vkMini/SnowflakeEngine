#include "sfpch.h"
#include "Shader.h"

#include "RendererCore/Renderer.h"

#include "Renderer/OpenGL/OpenGLShader.h"

namespace Snowflake {

	Ref<Shader> Shader::CreateShader(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create shader! No Rendering API was selected!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filepath);
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create shader! Unknown Rendering API!");
		return nullptr;
	}

}