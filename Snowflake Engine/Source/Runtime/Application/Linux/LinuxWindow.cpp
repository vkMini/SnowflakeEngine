#include "sfpch.h"
#include "LinuxWindow.h"

#include "Logging/Log.h"

#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "RendererCore/RendererContext.h"

#include <glad/glad.h>

#include <optick.h>

namespace Snowflake {

	static bool s_GLFWInitialized = false;

	LinuxWindow::LinuxWindow(const WindowSpecification& specs)
		: m_Specification(specs) {}

	LinuxWindow::~LinuxWindow()
	{
		Shutdown();
	}

	void LinuxWindow::Initialize()
	{
		OPTICK_EVENT();

		m_WindowData.Width = m_Specification.Width;
		m_WindowData.Height = m_Specification.Height;
		m_WindowData.Title = m_Specification.Title;

		SNOWFLAKE_ENGINE_INFO("Creating Window (Title: {}, Width: {}, Height: {})", m_Specification.Title, m_Specification.Width, m_Specification.Height);

		if (!s_GLFWInitialized)
		{
			int glfwInitSuccess = glfwInit();
			SNOWFLAKE_ENGINE_ASSERT(glfwInitSuccess, "Failed to create window '" + m_Specification.Title + "'! Failed to initialize GLFW!");

			glfwSetErrorCallback([](int errorCode, const char* errorMessage)
			{
				SNOWFLAKE_ENGINE_ERROR("A GLFW error occurred: {} (Error Code: {})", errorMessage, errorCode);
			});
		}

		glfwWindowHint(GLFW_MAXIMIZED, m_Specification.Maximized ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, m_Specification.Resizable ? GLFW_TRUE : GLFW_FALSE);

		if (m_Specification.Fullscreen)
		{
			GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

			m_WindowHandle = glfwCreateWindow((int)m_Specification.Width, (int)m_Specification.Height, m_Specification.Title.c_str(), primaryMonitor, nullptr);
		}
		else
		{
			m_WindowHandle = glfwCreateWindow((int)m_Specification.Width, (int)m_Specification.Height, m_Specification.Title.c_str(), nullptr, nullptr);
		}

		auto context = RendererContext::CreateContext(m_WindowHandle);
		context->Initialize();

		glfwSetWindowUserPointer(m_WindowHandle, &m_WindowData);
		SetVSyncEnabled(true);
		CenterWindow();

		// Setup GLFW window callbacks
		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int keycode, int action, int mods)
		{
			auto& windowData = *((WindowData*)glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key);
				windowData.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				windowData.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, true);
				windowData.EventCallback(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& windowData = *((WindowData*)glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				windowData.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				windowData.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& windowData = *((WindowData*)glfwGetWindowUserPointer(window));

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			windowData.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double xPos, double yPos)
		{
			auto& windowData = *((WindowData*)glfwGetWindowUserPointer(window));

			MouseMovedEvent event((float)xPos, (float)yPos);
			windowData.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
		{
			auto& windowData = *((WindowData*)glfwGetWindowUserPointer(window));

			WindowCloseEvent event;
			windowData.EventCallback(event);
		});

		glfwSetWindowFocusCallback(m_WindowHandle, [](GLFWwindow* window, int focused)
		{
			auto& windowData = *((WindowData*)glfwGetWindowUserPointer(window));

			switch (focused)
			{
				case GLFW_TRUE:
				{
					WindowFocusEvent event(focused);
					windowData.EventCallback(event);
					break;
				}
				case GLFW_FALSE:
				{
					WindowLostFocusEvent event(focused);
					windowData.EventCallback(event);
					break;
				}
			}
		});

		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
		{
			auto& windowData = *((WindowData*)glfwGetWindowUserPointer(window));
			windowData.Width = width;
			windowData.Height = height;

			WindowResizeEvent event(width, height);
			windowData.EventCallback(event);
		});

		glfwSetWindowPosCallback(m_WindowHandle, [](GLFWwindow* window, int xPos, int yPos)
		{
			auto& windowData = *((WindowData*)glfwGetWindowUserPointer(window));

			WindowMovedEvent event(xPos, yPos);
			windowData.EventCallback(event);
		});
	}

	void LinuxWindow::Shutdown()
	{
		OPTICK_EVENT();

		glfwDestroyWindow(m_WindowHandle);
		glfwTerminate();
	}


	void LinuxWindow::ProcessEvents()
	{
		OPTICK_EVENT();

		glfwPollEvents();
	}

	void LinuxWindow::SwapBuffers()
	{
		OPTICK_EVENT();

		glfwSwapBuffers(m_WindowHandle);
	}

	std::pair<uint32_t, uint32_t> LinuxWindow::GetPosition() const
	{
		OPTICK_EVENT();

		int xPos, yPos;
		glfwGetWindowPos(m_WindowHandle, &xPos, &yPos);

		return { (uint32_t)xPos, (uint32_t)yPos };
	}

	void LinuxWindow::SetVSyncEnabled(bool isEnabled)
	{
		OPTICK_EVENT();

		glfwSwapInterval(isEnabled ? GLFW_TRUE : GLFW_FALSE);
		m_WindowData.VSync = isEnabled;
	}

	void LinuxWindow::SetResizable(bool isResizable)
	{
		OPTICK_EVENT();

		glfwWindowHint(GLFW_RESIZABLE, isResizable ? GLFW_TRUE : GLFW_FALSE);
		m_WindowData.Resizable = isResizable;
	}

	void LinuxWindow::Maximize()
	{
		OPTICK_EVENT();

		if (!m_Specification.Fullscreen)
			glfwMaximizeWindow(m_WindowHandle);
		else
			SNOWFLAKE_ENGINE_ERROR("Failed to maximize window! Cannot maximize a fullscreen window!");
	}

	void LinuxWindow::CenterWindow()
	{
		OPTICK_EVENT();

		if (!m_Specification.Fullscreen)
		{
			const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			glfwSetWindowMonitor(m_WindowHandle,
				nullptr,
				(videoMode->width / 2) - (m_WindowData.Width / 2),
				(videoMode->height / 2) - (m_WindowData.Height / 2),
				m_WindowData.Width,
				m_WindowData.Height,
				videoMode->refreshRate);
		}
		else
		{
			SNOWFLAKE_ENGINE_ERROR("Failed to center window! Cannot center a fullscreen window!");
		}
	}

	void LinuxWindow::SetTitle(const std::string& title)
	{
		OPTICK_EVENT();

		glfwSetWindowTitle(m_WindowHandle, title.c_str());
		m_WindowData.Title = title;
	}
}