#include "sfpch.h"
#include "Application.h"

#include "Core/Core.h"

#include "Logging/Log.h"
#include "Events/ApplicationEvent.h"

#include "Input/Input.h"

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
			glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

		/* Render a Triangle */

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		unsigned int indices[3] = {
			0, 1, 2
		};

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		/*-------------------*/
	}

	
	void Application::Shutdown()
	{

	}

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

	/*--------*/
	/* Events */
	/*--------*/

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		Quit();

		return false;
	}

}