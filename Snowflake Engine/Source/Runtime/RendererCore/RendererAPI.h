#pragma once

namespace Snowflake {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,

			OpenGL, Vulkan, DirectX, Metal
		};

		static API GetAPI() { return s_RendererAPI; }
		static void SetAPI(API api) { s_RendererAPI = api; }
	private:
		static API s_RendererAPI;
	};
}