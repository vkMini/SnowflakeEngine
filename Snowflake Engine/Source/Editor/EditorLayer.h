#pragma once

#include "Core/Core.h"
#include "Camera/OrthographicCameraController.h"

#include "RendererCore/Shader.h"
#include "RendererCore/VertexArray.h"
#include "RendererCore/Texture.h"
#include "RendererCore/Framebuffer.h"

#include "Layers/Layer.h"

namespace Snowflake {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnFixedUpdate(Snowflake::Time deltaTime) override;

		virtual void OnImGuiRender() override;

		virtual void OnEvent(Snowflake::Event& event) override;
	private:
		Snowflake::Ref<Snowflake::Shader> m_Shader;
		Snowflake::Ref<Snowflake::VertexArray> m_VertexArray;
		Snowflake::Ref<Snowflake::VertexBuffer> m_VertexBuffer;
		Snowflake::Ref<Snowflake::IndexBuffer> m_IndexBuffer;

		Snowflake::Ref<Snowflake::Texture2D> m_MarioTexture;
		Snowflake::Ref<Snowflake::Texture2D> m_LuigiTexture;
		Snowflake::Ref<Snowflake::Texture2D> m_CheckerboardTexture;

		Snowflake::Ref<Snowflake::Framebuffer> m_Framebuffer;

		Snowflake::OrthographicCameraController m_CameraController;
	};
}