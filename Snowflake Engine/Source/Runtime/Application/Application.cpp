#include "sfpch.h"
#include "Application.h"

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
		
	}

	
	void Application::Shutdown()
	{

	}

}