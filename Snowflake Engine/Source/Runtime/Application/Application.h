#pragma once

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
	private:
		bool m_IsRunning = true;
	};

	// Defined in the client application
	Application* CreateApplication();

}

