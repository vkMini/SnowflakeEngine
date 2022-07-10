#include "sfpch.h"
#include "Renderer.h"

#include "RendererCommand.h"

namespace Snowflake {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<SceneData>();

	void Renderer::BeginScene(OrthographicCamera& orthographicCamera)
	{
		s_SceneData->ViewProjectionMatrix = orthographicCamera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{

	}

}