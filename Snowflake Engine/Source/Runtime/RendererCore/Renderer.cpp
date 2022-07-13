#include "sfpch.h"
#include "Renderer.h"

#include "Renderer2D.h"
#include "RendererCommand.h"

namespace Snowflake {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<SceneData>();

	void Renderer::Initialize()
	{
		RendererCommand::Initialize();
		Renderer2D::Initialize();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::BeginScene(OrthographicCamera& orthographicCamera)
	{
		s_SceneData->ViewProjectionMatrix = orthographicCamera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{

	}

}