#include "sfpch.h"
#include "RendererCommand.h"

namespace Snowflake {

	Scope<RendererAPI> RendererCommand::s_RendererAPI = RendererAPI::CreateAPI();

	void RendererCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RendererCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RendererCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}

}