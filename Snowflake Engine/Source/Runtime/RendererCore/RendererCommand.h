#pragma once

#include "RendererAPI.h"

#include "VertexArray.h"

namespace Snowflake {

	class RendererCommand
	{
	public:
		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void DrawIndexed(const Ref<VertexArray>& vertexArray);
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}