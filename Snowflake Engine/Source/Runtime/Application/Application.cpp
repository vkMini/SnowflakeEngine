#include "sfpch.h"
#include "Application.h"

#include "Core/Core.h"

#include "Logging/Log.h"
#include "Events/ApplicationEvent.h"

#include "Input/Input.h"

#include "RendererCore/Renderer.h"
#include "RendererCore/RendererCommand.h"

#include <glad/glad.h>

extern bool bIsApplicationRunning;

namespace Snowflake {

	Application* Application::s_ApplicationInstance = nullptr;

	Application::Application()
	{
		Initialize();
	}

	Application::~Application()
	{
		Shutdown();
	}

	void Application::Start()
	{
		while (m_IsRunning)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_AppWindow->ProcessEvents();
			m_AppWindow->SwapBuffers();
		}
	}

	void Application::Restart()
	{
		// By terminating the loop owned by m_IsRunning, the loop owned by bIsApplicationRunning will create a new instance of the engine, after shutdown.
		m_IsRunning = false;
	}

	void Application::Quit()
	{
		m_IsRunning = false;
		bIsApplicationRunning = false;
	}

	/*---------------------------------------*/
	/* Initialization and shutdown functions */
	/*---------------------------------------*/

	void Application::Initialize()
	{
		s_ApplicationInstance = this;

		m_AppWindow = Window::CreateWindow();
		m_AppWindow->Initialize();
		m_AppWindow->SetEventCallbackFunction(SNOWFLAKE_BIND_EVENT_FUNCTION(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);

		Input::Initialize();
	}

	
	void Application::Shutdown()
	{

	}

	/*--------*/
	/* Events */
	/*--------*/

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(SNOWFLAKE_BIND_EVENT_FUNCTION(Application::OnWindowClose));

		for (auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it)
		{
			if (event.isHandled)
				break;
			(*it)->OnEvent(event);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		Quit();

		return false;
	}

}