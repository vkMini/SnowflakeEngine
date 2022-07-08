#include "sfpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Snowflake {

	OpenGLContext::OpenGLContext(void* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SNOWFLAKE_ENGINE_ASSERT(windowHandle, "Failed to create an OpenGL context! Window handle is null!");
	}

	void OpenGLContext::Initialize()
	{
		auto window = static_cast<GLFWwindow*>(m_WindowHandle);

		glfwMakeContextCurrent(window);
		SNOWFLAKE_CLIENT_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to create an OpenGL context! Failed to initialize Glad!");

		SNOWFLAKE_ENGINE_INFO("OpenGL Renderer Info:");
		SNOWFLAKE_ENGINE_INFO("  Vendor: {}", glGetString(GL_VENDOR));
		SNOWFLAKE_ENGINE_INFO("  Renderer: {}", glGetString(GL_RENDERER));
		SNOWFLAKE_ENGINE_INFO("  Version: {}", glGetString(GL_VERSION));

		SNOWFLAKE_ENGINE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 3), "Failed to create an OpenGL context! Snowflake Engine requires OpenGL 4.3 or higher!");
	}

}