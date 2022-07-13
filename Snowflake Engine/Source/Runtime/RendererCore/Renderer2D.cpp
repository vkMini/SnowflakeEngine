#include "sfpch.h"
#include "Renderer2D.h"

#include "Shader.h"
#include "VertexArray.h"

#include "RendererCommand.h"

namespace Snowflake {

	struct RendererData
	{
		Ref<Shader> FlatColorShader;
		Ref<VertexArray> QuadVertexArray;
	};

	static RendererData s_RendererData;

	void Renderer2D::Initialize()
	{
		float vertices[3 * 4] = {
		  -0.5f, -0.5f, 0.0f,
		   0.5f, -0.5f, 0.0f,
		   0.5f,  0.5f, 0.0f,
		  -0.5f,  0.5f, 0.0f
		};

		unsigned int indices[6] = {
			0, 1, 2, 2, 3, 0
		};

		s_RendererData.FlatColorShader = Shader::CreateShader("Assets/Shaders/FlatColor.glsl");

		s_RendererData.QuadVertexArray = VertexArray::CreateVertexArray();

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::CreateBuffer(vertices, sizeof(vertices));
		vertexBuffer->SetBufferLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});

		Ref<IndexBuffer> indexBuffer = IndexBuffer::CreateBuffer(indices, sizeof(indices) / sizeof(uint32_t));
		s_RendererData.QuadVertexArray->SetIndexBuffer(indexBuffer);

		s_RendererData.QuadVertexArray->AddVertexBuffer(vertexBuffer);
	}

	void Renderer2D::Shutdown()
	{

	}

	void Renderer2D::BeginScene(const OrthographicCamera& orthographicCamera)
	{
		s_RendererData.FlatColorShader->Bind();
		s_RendererData.FlatColorShader->SetMat4("u_ViewProjection", orthographicCamera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f)) * 
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0.0f));

		s_RendererData.FlatColorShader->Bind();
		s_RendererData.FlatColorShader->SetFloat4("u_Color", color);
		s_RendererData.FlatColorShader->SetMat4("u_Transform", transform);

		s_RendererData.QuadVertexArray->Bind();

		RendererCommand::DrawIndexed(s_RendererData.QuadVertexArray);
	}

}