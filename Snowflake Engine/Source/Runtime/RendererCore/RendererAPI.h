#pragma once

#include "Core/Core.h"

#include "VertexArray.h"

#include <glm/glm.hpp>

namespace Snowflake {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,

			OpenGL, Vulkan, DirectX, Metal
		};

		virtual void Intialize() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		static API GetAPI() { return s_RendererAPI; }
		static void SetAPI(API api) { s_RendererAPI = api; }

		static Scope<RendererAPI> CreateAPI();
	private:
		static API s_RendererAPI;
	};
}