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

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return s_RendererAPI; }
		static void SetAPI(API api) { s_RendererAPI = api; }

		static Scope<RendererAPI> CreateAPI();
	private:
		static API s_RendererAPI;
	};
}