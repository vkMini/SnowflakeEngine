#include "sfpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <optick.h>

namespace Snowflake {

	OpenGLContext::OpenGLContext(void* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SNOWFLAKE_ENGINE_ASSERT(windowHandle, "Failed to create an OpenGL context! Window handle is null!");
	}

	void OpenGLContext::Initialize()
	{
		OPTICK_EVENT();

		auto window = static_cast<GLFWwindow*>(m_WindowHandle);

		glfwMakeContextCurrent(window);
		int gladInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SNOWFLAKE_CLIENT_ASSERT(gladInitSuccess, "Failed to create an OpenGL context! Failed to initialize Glad!");

		SNOWFLAKE_ENGINE_INFO("OpenGL Renderer Info:");
		SNOWFLAKE_ENGINE_INFO("  Vendor: {}", glGetString(GL_VENDOR));
		SNOWFLAKE_ENGINE_INFO("  Renderer: {}", glGetString(GL_RENDERER));
		SNOWFLAKE_ENGINE_INFO("  Version: {}", glGetString(GL_VERSION));

		SNOWFLAKE_ENGINE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Failed to create an OpenGL context! Snowflake Engine requires OpenGL 4.5 or higher!");
	}

}