#include "sfpch.h"
#include "Renderer.h"

#include "RendererCommand.h"

namespace Snowflake {

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		vertexArray->Bind();

		RendererCommand::DrawIndexed(vertexArray);
	}

}