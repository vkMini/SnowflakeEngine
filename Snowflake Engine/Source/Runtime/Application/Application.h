#pragma once

#include "Events/ApplicationEvent.h"

#include "Window.h"

#include "Layers/LayerStack.h"

namespace Snowflake {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Start();
		void Restart();
		void Quit();

		// Layers
		void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); layer->OnAttach(); }
		void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); overlay->OnAttach(); }

		static Application& GetInstance() { return *s_ApplicationInstance; }

		Window& GetWindow() { return *m_AppWindow; }
	private:
		// Used to initialize the engine when running it
		void Initialize();

		// Used to shutdown and close and instance of the engine
		void Shutdown();

		// Events
		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& event);
	private:
		static Application* s_ApplicationInstance;

		Scope<Window> m_AppWindow;

		LayerStack m_LayerStack;

		bool m_IsRunning = true;
	};

	// Defined in the client application
	Application* CreateApplication();

}

