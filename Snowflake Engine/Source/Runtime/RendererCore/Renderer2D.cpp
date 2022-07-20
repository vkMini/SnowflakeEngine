#include "sfpch.h"
#include "Renderer2D.h"

#include "Shader.h"
#include "VertexArray.h"

#include "RendererCommand.h"

#include <optick.h>

namespace Snowflake {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoord;
		// TODO: Texture IDs
	};

	struct RendererData
	{
		Ref<Shader> DefaultShader;
		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Texture2D> WhiteTexture;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		uint32_t QuadIndexCount = 0;
	};

	static RendererData s_RendererData;

	void Renderer2D::Initialize()
	{
		OPTICK_EVENT();

		s_RendererData.DefaultShader = Shader::CreateShader("Assets/Shaders/Default.glsl");
		s_RendererData.DefaultShader->Bind();
		s_RendererData.DefaultShader->SetInt("u_Texture", 0);

		s_RendererData.QuadVertexArray = VertexArray::CreateVertexArray();

		s_RendererData.QuadVertexBuffer = VertexBuffer::CreateBuffer(s_RendererData.MaxVertices * sizeof(QuadVertex));
		s_RendererData.QuadVertexBuffer->SetBufferLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TextureCoord" }
		});

		s_RendererData.QuadVertexBufferBase = new QuadVertex[s_RendererData.MaxVertices];

		uint32_t* indices = new uint32_t[s_RendererData.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_RendererData.MaxIndices; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> indexBuffer = IndexBuffer::CreateBuffer(indices, s_RendererData.MaxIndices);
		s_RendererData.QuadVertexArray->SetIndexBuffer(indexBuffer);

		delete[] indices;

		s_RendererData.QuadVertexArray->AddVertexBuffer(s_RendererData.QuadVertexBuffer);
		
		s_RendererData.WhiteTexture = Texture2D::CreateTexture2D(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_RendererData.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
	}

	void Renderer2D::Shutdown()
	{
		OPTICK_EVENT();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& orthographicCamera)
	{
		OPTICK_EVENT();

		s_RendererData.DefaultShader->Bind();
		s_RendererData.DefaultShader->SetMat4("u_ViewProjection", orthographicCamera.GetViewProjectionMatrix());

		s_RendererData.QuadIndexCount = 0;
		s_RendererData.QuadVertexBufferPtr = s_RendererData.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		OPTICK_EVENT();

		uint32_t dataSize = (uint8_t*)s_RendererData.QuadVertexBufferPtr - (uint8_t*)s_RendererData.QuadVertexBufferBase;
		s_RendererData.QuadVertexBuffer->SetData(s_RendererData.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		RendererCommand::DrawIndexed(s_RendererData.QuadVertexArray, s_RendererData.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		OPTICK_EVENT();

		s_RendererData.QuadVertexBufferPtr->Position = { position.x, position.y, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float titlingFactor, const glm::vec4& tintColor)
	{
		OPTICK_EVENT();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0.0f));

		texture->Bind();

		s_RendererData.DefaultShader->SetFloat("u_TilingFactor", titlingFactor);
		s_RendererData.DefaultShader->SetFloat4("u_Color", tintColor);
		s_RendererData.DefaultShader->SetFloat4("u_TintColor", tintColor);
		s_RendererData.DefaultShader->SetMat4("u_Transform", transform);

		s_RendererData.QuadVertexArray->Bind();

		RendererCommand::DrawIndexed(s_RendererData.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		OPTICK_EVENT();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0.0f));

		s_RendererData.DefaultShader->SetFloat4("u_Color", color);
		s_RendererData.DefaultShader->SetMat4("u_Transform", transform);

		s_RendererData.WhiteTexture->Bind();

		s_RendererData.QuadVertexArray->Bind();

		RendererCommand::DrawIndexed(s_RendererData.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		OPTICK_EVENT();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0.0f));

		texture->Bind();

		s_RendererData.DefaultShader->SetFloat("u_TilingFactor", tilingFactor);
		s_RendererData.DefaultShader->SetFloat4("u_Color", tintColor);
		s_RendererData.DefaultShader->SetFloat4("u_TintColor", tintColor);
		s_RendererData.DefaultShader->SetMat4("u_Transform", transform);

		s_RendererData.QuadVertexArray->Bind();

		RendererCommand::DrawIndexed(s_RendererData.QuadVertexArray);
	}

}