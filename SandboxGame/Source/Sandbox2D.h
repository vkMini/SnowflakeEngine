#pragma once

#include <Snowflake.h>

class Sandbox2D : public Snowflake::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate() override;
	virtual void OnFixedUpdate(Snowflake::Time deltaTime) override;

	virtual void OnEvent(Snowflake::Event& event) override;
private:
	Snowflake::Ref<Snowflake::Shader> m_Shader;
	Snowflake::Ref<Snowflake::VertexArray> m_VertexArray;
	Snowflake::Ref<Snowflake::VertexBuffer> m_VertexBuffer;
	Snowflake::Ref<Snowflake::IndexBuffer> m_IndexBuffer;

	Snowflake::Ref<Snowflake::Texture2D> m_MarioTexture;

	Snowflake::OrthographicCameraController m_CameraController;
};

