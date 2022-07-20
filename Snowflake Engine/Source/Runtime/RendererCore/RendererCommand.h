#pragma once

#include "RendererAPI.h"

#include "VertexArray.h"

namespace Snowflake {

	class RendererCommand
	{
	public:
		static void Initialize();

		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}