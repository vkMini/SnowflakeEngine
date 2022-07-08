#include "sfpch.h"
#include "MacInput.h"

#include "Application/Application.h"

#include <GLFW/glfw3.h>

namespace Snowflake {

	bool MacInput::GetKeyDownImpl(KeyCode keyCode)
	{
		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int keyState = glfwGetKey(appWindow, keyCode);

		return keyState == GLFW_PRESS;
	}

	bool MacInput::GetKeyUpImpl(KeyCode keyCode)
	{
		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int keyState = glfwGetKey(appWindow, keyCode);

		return keyState == GLFW_RELEASE;
	}

	bool MacInput::GetMouseButtonDownImpl(MouseButton mouseButton)
	{
		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int mouseButtonState = glfwGetMouseButton(appWindow, mouseButton);

		return mouseButtonState == GLFW_PRESS;
	}

	bool MacInput::GetMouseButtonUpImpl(MouseButton mouseButton)
	{
		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int mouseButtonState = glfwGetMouseButton(appWindow, mouseButton);

		return mouseButtonState == GLFW_RELEASE;
	}

	glm::vec2 MacInput::GetMousePositionImpl()
	{
		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		double xPos, yPos;

		glfwGetCursorPos(appWindow, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float MacInput::GetMouseXImpl()
	{
		return GetMousePosition().x;
	}

	float MacInput::GetMouseYImpl()
	{
		return GetMousePosition().y;
	}

}