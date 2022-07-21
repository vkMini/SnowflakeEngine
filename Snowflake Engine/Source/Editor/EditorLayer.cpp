#include "sfpch.h"
#include "EditorLayer.h"

#include "Application/Application.h"

#include "RendererCore/RendererCommand.h"
#include "RendererCore/Renderer2D.h"

#include <imgui.h>

namespace Snowflake {

	EditorLayer::EditorLayer()
		: Layer("Snowstorm Editor"), m_CameraController((float)Application::GetInstance().GetWindow().GetWidth() / (float)Application::GetInstance().GetWindow().GetHeight()) {}

	void EditorLayer::OnAttach()
	{
		m_CheckerboardTexture = Texture2D::CreateTexture2D("Assets/Textures/Checkerboard.png");
		m_MarioTexture = Texture2D::CreateTexture2D("Assets/Textures/Mario.png");
		m_LuigiTexture = Texture2D::CreateTexture2D("Assets/Textures/Luigi.png");

		FramebufferSpecification framebufferSpec;
		framebufferSpec.Width = Application::GetInstance().GetWindow().GetWidth();
		framebufferSpec.Height = Application::GetInstance().GetWindow().GetHeight();

		m_Framebuffer = Framebuffer::CreateFramebuffer(framebufferSpec);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate()
	{
		static float rotation = 0.0f;
		rotation += Application::GetInstance().GetDeltaTime() * 30.0f;

		Renderer2D::ResetStats();

		m_Framebuffer->Bind();

		RendererCommand::SetClearColor({ 0.45f, 0.55f, 0.60f, 1.0f });
		RendererCommand::Clear();

		Renderer2D::BeginScene(m_CameraController.GetCamera());

		Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f }); // Red
		Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 0.7f, 0.7f }, rotation, { 0.8f, 0.8f, 0.2f, 1.0f }); // Yellow
		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.8f, 0.3f, 1.0f });  // Green
		Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.3f, 0.8f, 1.0f });  // Blue

		Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, m_MarioTexture);
		Renderer2D::DrawQuad({ 0.0f, -1.0f }, { 1.0f, 1.0f }, m_LuigiTexture);

		Renderer2D::EndScene();

		m_Framebuffer->Unbind();

		m_Framebuffer->Bind();

		Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 0.5f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Renderer2D::DrawQuad({ x + 0.3f, y }, { 0.45f, 0.45f }, color);
			}
		}

		Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f }, { 20.0f, 20.0f }, 0.0f, m_CheckerboardTexture, 10.0f);

		Renderer2D::EndScene();

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnFixedUpdate(Time deltaTime)
	{
		m_CameraController.OnFixedUpdate(deltaTime);
	}

	void EditorLayer::OnImGuiRender()
	{
		/*-----------*/
		/* Dockspace */
		/*-----------*/

		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
					Application::GetInstance().Quit();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();

		/*-----------*/
		/*-----------*/
		/*-----------*/

		/*---------------------*/
		/* Renderer Statistics */
		/*---------------------*/

		auto rendererStats = Renderer2D::GetStats();

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

		/*---------------------*/
		/*---------------------*/
		/*---------------------*/


		/*----------------*/
		/* Scene Viewport */
		/*----------------*/

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

		ImGui::Begin("Scene Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		if (m_ViewportSize != *((glm::vec2*) & viewportPanelSize))
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

			m_CameraController.ResizeBounds(viewportPanelSize.x, viewportPanelSize.y);
		}

		ImGui::Image((void*)m_Framebuffer->GetColorAttachmentHandle(), { m_ViewportSize.x, m_ViewportSize.y }, { 0, 1 }, { 1, 0 });

		ImGui::PopStyleVar();
		
		ImGui::End();

		/*----------------*/
		/*----------------*/
		/*----------------*/
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);
	}

}