#pragma once

#include "Events/ApplicationEvent.h"

#include "Window.h"

namespace Snowflake {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Start();
		void Restart();
		void Quit();
	private:
		// Used to initialize the engine when running it
		void Initialize();

		// Used to shutdown and close and instance of the engine
		void Shutdown();

		// Events
		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& event);
	private:
		Scope<Window> m_AppWindow;

		bool m_IsRunning = true;
	};

	// Defined in the client application
	Application* CreateApplication();

}

