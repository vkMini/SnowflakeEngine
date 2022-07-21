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
		float TextureIndex;
		float TilingFactor;
	};

	struct RendererData
	{
		Ref<Shader> DefaultShader;
		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Texture2D> WhiteTexture;

		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		Renderer2D::Statistics RendererStats;
		
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: Add Renderer Capabilities

		uint32_t QuadIndexCount = 0;
		uint32_t TextureSlotIndex = 1; // This doesn't start at 0 because index 0 is going to hold the white texture

		glm::vec4 QuadVertexPositions[4];

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;

	};

	static RendererData s_RendererData;

	void Renderer2D::Initialize()
	{
		OPTICK_EVENT();

		int32_t samplers[s_RendererData.MaxTextureSlots];
		for (uint32_t i = 0; i < s_RendererData.MaxTextureSlots; i++)
			samplers[i] = i;

		s_RendererData.DefaultShader = Shader::CreateShader("Assets/Shaders/Default.glsl");
		s_RendererData.DefaultShader->Bind();
		s_RendererData.DefaultShader->SetIntArray("u_Textures", samplers, s_RendererData.MaxTextureSlots);

		s_RendererData.QuadVertexArray = VertexArray::CreateVertexArray();

		s_RendererData.QuadVertexBuffer = VertexBuffer::CreateBuffer(s_RendererData.MaxVertices * sizeof(QuadVertex));
		s_RendererData.QuadVertexBuffer->SetBufferLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TextureCoord" },
			{ ShaderDataType::Float, "a_TextureIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
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

		s_RendererData.TextureSlots[0] = s_RendererData.WhiteTexture;

		s_RendererData.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_RendererData.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_RendererData.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_RendererData.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
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

		s_RendererData.TextureSlotIndex = 1;
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
		OPTICK_EVENT();

		// Bind textures
		for (uint32_t i = 0; i < s_RendererData.TextureSlotIndex; i++)
			s_RendererData.TextureSlots[i]->Bind(i);

		RendererCommand::DrawIndexed(s_RendererData.QuadVertexArray, s_RendererData.QuadIndexCount);

		s_RendererData.RendererStats.DrawCalls++;
	}

	void Renderer2D::FlushAndReset()
	{
		OPTICK_EVENT();

		EndScene();

		s_RendererData.QuadIndexCount = 0;
		s_RendererData.QuadVertexBufferPtr = s_RendererData.QuadVertexBufferBase;

		s_RendererData.TextureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		OPTICK_EVENT();

		if (s_RendererData.QuadIndexCount > RendererData::MaxIndices)
			FlushAndReset();

		const float textureIndex = 0.0f; // This will always be 0 so the white texture can be used.
		const float tilingFactor = 1.0f; // We are sampling from the white texture, so this must be 1.

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[0];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[1];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[2];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[3];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.RendererStats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		OPTICK_EVENT();

		if (s_RendererData.QuadIndexCount > RendererData::MaxIndices)
			FlushAndReset();

		constexpr glm::vec4 color = glm::vec4(1.0f);

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_RendererData.TextureSlotIndex; i++)
		{
			if (*s_RendererData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_RendererData.TextureSlotIndex;
			s_RendererData.TextureSlots[textureIndex] = texture;
			s_RendererData.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[0];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[1];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[2];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[3];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.RendererStats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		OPTICK_EVENT();

		if (s_RendererData.QuadIndexCount > RendererData::MaxIndices)
			FlushAndReset();

		const float textureIndex = 0.0f; // This will always be 0 so the white texture can be used.
		const float tilingFactor = 1.0f; // We are sampling from the white textures, so this must be 1.

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0.0f));

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[0];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[1];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[2];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[3];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.RendererStats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		OPTICK_EVENT();

		if (s_RendererData.QuadIndexCount > RendererData::MaxIndices)
			FlushAndReset();

		constexpr glm::vec4 color = glm::vec4(1.0f);

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_RendererData.TextureSlotIndex; i++)
		{
			if (*s_RendererData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_RendererData.TextureSlotIndex;
			s_RendererData.TextureSlots[textureIndex] = texture;
			s_RendererData.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[0];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[1];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 0.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[2];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 1.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadVertexBufferPtr->Position = transform * s_RendererData.QuadVertexPositions[3];
		s_RendererData.QuadVertexBufferPtr->Color = color;
		s_RendererData.QuadVertexBufferPtr->TextureCoord = { 0.0f, 1.0f };
		s_RendererData.QuadVertexBufferPtr->TextureIndex = textureIndex;
		s_RendererData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RendererData.QuadVertexBufferPtr++;

		s_RendererData.QuadIndexCount += 6;

		s_RendererData.RendererStats.QuadCount++;
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_RendererData.RendererStats;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_RendererData.RendererStats, 0, sizeof(Statistics));
	}

}