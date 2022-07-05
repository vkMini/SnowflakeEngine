#include "sfpch.h"
#include "Application.h"

#include "Core/Core.h"

#include "Logging/Log.h"
#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

extern bool bIsApplicationRunning;

namespace Snowflake {

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
			glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_AppWindow->ProcessEvents();
			m_AppWindow->SwapBuffers();
		}
	}

	void Application::Restart()
	{
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
		m_AppWindow = Window::CreateWindow();
		m_AppWindow->Initialize();
		m_AppWindow->SetEventCallbackFunction(SNOWFLAKE_BIND_EVENT_FUNCTION(Application::OnEvent));
	}

	
	void Application::Shutdown()
	{

	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(SNOWFLAKE_BIND_EVENT_FUNCTION(Application::OnWindowClose));

		SNOWFLAKE_ENGINE_DEBUG(event);
	}

	/*--------*/
	/* Events */
	/*--------*/

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		Quit();

		return false;
	}

}