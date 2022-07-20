#include "sfpch.h"
#include "Renderer.h"

#include "Renderer2D.h"
#include "RendererCommand.h"

#include <optick.h>

namespace Snowflake {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<SceneData>();

	void Renderer::Initialize()
	{
		OPTICK_EVENT();

		RendererCommand::Initialize();
		Renderer2D::Initialize();
	}

	void Renderer::Shutdown()
	{
		OPTICK_EVENT();

		Renderer2D::Shutdown();
	}

	void Renderer::BeginScene(OrthographicCamera& orthographicCamera)
	{
		OPTICK_EVENT();

		s_SceneData->ViewProjectionMatrix = orthographicCamera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		OPTICK_EVENT();

		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{
		OPTICK_EVENT();
	}

}