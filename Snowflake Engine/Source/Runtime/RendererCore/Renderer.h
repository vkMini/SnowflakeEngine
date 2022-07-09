#pragma once

#include "RendererAPI.h"

#include "Shader.h"
#include "VertexArray.h"

namespace Snowflake {

	class Renderer
	{
	public:
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
