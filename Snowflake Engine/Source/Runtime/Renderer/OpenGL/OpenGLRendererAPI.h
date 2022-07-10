#pragma once

#include "RendererCore/RendererAPI.h"

#include "RendererCore/VertexArray.h"

namespace Snowflake {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Intialize() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}