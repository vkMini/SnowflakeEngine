#include "sfpch.h"
#include "RendererCommand.h"

namespace Snowflake {

	Scope<RendererAPI> RendererCommand::s_RendererAPI = RendererAPI::CreateAPI();

	void RendererCommand::Initialize()
	{
		s_RendererAPI->Intialize();
	}

	void RendererCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RendererCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RendererCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	void RendererCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}

}