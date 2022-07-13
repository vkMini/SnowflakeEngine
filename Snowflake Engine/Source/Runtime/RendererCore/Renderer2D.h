#pragma once

#include "Camera/OrthographicCamera.h"

#include "RendererCore/Texture.h"

#include <glm/glm.hpp>

namespace Snowflake {

	class Renderer2D
	{
	public:
		static void Initialize();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& orthographicCamera);
		static void EndScene();

		/* Primitives */
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};

}
