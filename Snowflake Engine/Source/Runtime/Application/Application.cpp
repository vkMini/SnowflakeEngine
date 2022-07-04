#include "sfpch.h"
#include "Application.h"

#include "Logging/Log.h"
#include "Events/ApplicationEvent.h"

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
		// Event System test
		WindowResizeEvent e(3860, 2160);
		SNOWFLAKE_ENGINE_DEBUG(e);
	}

	
	void Application::Shutdown()
	{

	}

}