#include "sfpch.h"
#include "LinuxWindow.h"

#include "Logging/Log.h"

#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

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

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

		glfwMakeContextCurrent(m_WindowHandle);
		SNOWFLAKE_ENGINE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to create an OpenGL context!");

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
		glfwDestroyWindow(m_WindowHandle);
		glfwTerminate();
	}


	void LinuxWindow::ProcessEvents()
	{
		glfwPollEvents();
	}

	void LinuxWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	std::pair<uint32_t, uint32_t> LinuxWindow::GetPosition() const
	{
		int xPos, yPos;
		glfwGetWindowPos(m_WindowHandle, &xPos, &yPos);

		return { (uint32_t)xPos, (uint32_t)yPos };
	}

	void LinuxWindow::SetVSyncEnabled(bool isEnabled)
	{
		glfwSwapInterval(isEnabled ? GLFW_TRUE : GLFW_FALSE);
		m_WindowData.VSync = isEnabled;
	}

	void LinuxWindow::SetResizable(bool isResizable)
	{
		glfwWindowHint(GLFW_RESIZABLE, isResizable ? GLFW_TRUE : GLFW_FALSE);
		m_WindowData.Resizable = isResizable;
	}

	void LinuxWindow::Maximize()
	{
		if (!m_Specification.Fullscreen)
			glfwMaximizeWindow(m_WindowHandle);
		else
			SNOWFLAKE_ENGINE_ERROR("Failed to maximize window! Cannot maximize a fullscreen window!");
	}

	void LinuxWindow::CenterWindow()
	{
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
		glfwSetWindowTitle(m_WindowHandle, title.c_str());
		m_WindowData.Title = title;
	}
}