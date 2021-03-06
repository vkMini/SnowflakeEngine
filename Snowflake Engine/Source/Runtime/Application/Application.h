#pragma once

#include "Time/Time.h"

#include "Events/ApplicationEvent.h"

#include "Window.h"

#include "Layers/LayerStack.h"
#include "UI/ImGuiLayer.h"

namespace Snowflake {

	class Application
	{
	public:
		Application(const std::string& name = "Snowflake Engine");
		virtual ~Application();

		void Start();
		void Restart();
		void Quit();

		// Layers
		void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); layer->OnAttach(); }
		void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); overlay->OnAttach(); }

		static Application& GetInstance() { return *s_ApplicationInstance; }

		Window& GetWindow() { return *m_AppWindow; }

		float GetDeltaTime() { return m_DeltaTime; }
	private:
		// Used to initialize the engine when running it
		void Initialize();

		// Used to shutdown and close and instance of the engine
		void Shutdown();

		// Events
		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		static Application* s_ApplicationInstance;

		Scope<Window> m_AppWindow;

		ImGuiLayer* m_ImGuiLayer;

		Time m_DeltaTime;
		LayerStack m_LayerStack;

		std::string m_ApplicationName;

		float m_LastFrameTime = 0.0f;

		bool m_IsWindowMinimized = false;
		bool m_IsRunning = true;
	};

	// Defined in the client application
	Application* CreateApplication();

}

