#include "Sandbox2D.h"

#include <imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController((float)Snowflake::Application::GetInstance().GetWindow().GetWidth() / (float)Snowflake::Application::GetInstance().GetWindow().GetHeight()) {}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Snowflake::Texture2D::CreateTexture2D("Assets/Textures/Checkerboard.png");
	m_MarioTexture = Snowflake::Texture2D::CreateTexture2D("Assets/Textures/Mario.png");
	m_LuigiTexture = Snowflake::Texture2D::CreateTexture2D("Assets/Textures/Luigi.png");
} 

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate()
{
	static float rotation = 0.0f;
	rotation += Snowflake::Application::GetInstance().GetDeltaTime() * 20.0f;

	Snowflake::Renderer2D::ResetStats();

	Snowflake::RendererCommand::SetClearColor({ 0.45f, 0.55f, 0.60f, 1.0f });
	Snowflake::RendererCommand::Clear();

	Snowflake::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Snowflake::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f }); // Red
	Snowflake::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 0.7f, 0.7f }, rotation, { 0.8f, 0.8f, 0.2f, 1.0f }); // Yellow
	Snowflake::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });  // Green
	Snowflake::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.3f, 0.8f, 1.0f });  // Blue

	Snowflake::Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, m_MarioTexture);
	Snowflake::Renderer2D::DrawQuad({ 0.0f, -1.0f }, { 1.0f, 1.0f }, m_LuigiTexture);

	Snowflake::Renderer2D::EndScene();

	Snowflake::Renderer2D::BeginScene(m_CameraController.GetCamera());

	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = { (x + 0.5f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			Snowflake::Renderer2D::DrawQuad({ x + 0.3f, y }, { 0.45f, 0.45f }, color);
		}
	}

	Snowflake::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 20.0f, 20.0f }, 0.0f, m_CheckerboardTexture, 10.0f);

	Snowflake::Renderer2D::EndScene();
}

void Sandbox2D::OnFixedUpdate(Snowflake::Time deltaTime)
{
	m_CameraController.OnFixedUpdate(deltaTime);
}

void Sandbox2D::OnImGuiRender()
{
	auto rendererStats = Snowflake::Renderer2D::GetStats();

	ImGui::Begin("Performance");

	if (ImGui::TreeNode("Renderer Statistics"))
	{
		ImGui::Text("Draw Calls: %d", rendererStats.DrawCalls);
		ImGui::Text("Quads: %d", rendererStats.QuadCount);
		ImGui::Text("Vertices: %d", rendererStats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", rendererStats.GetTotalIndexCount());

		ImGui::TreePop();
	}

	ImGui::End();
}

void Sandbox2D::OnEvent(Snowflake::Event& event)
{
	m_CameraController.OnEvent(event);
}
