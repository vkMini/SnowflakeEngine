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
		virtual void OnFixedUpdate(Time deltaTime) override;

		virtual void OnImGuiRender() override;

		virtual void OnEvent(Event& event) override;
	private:
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;

		Ref<Texture2D> m_MarioTexture;
		Ref<Texture2D> m_LuigiTexture;
		Ref<Texture2D> m_CheckerboardTexture;

		Ref<Framebuffer> m_Framebuffer;

		OrthographicCameraController m_CameraController;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	};
}