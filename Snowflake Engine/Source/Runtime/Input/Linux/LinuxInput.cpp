#include "sfpch.h"
#include "LinuxInput.h"

#include "Application/Application.h"

#include <GLFW/glfw3.h>

#include <optick.h>

namespace Snowflake {

	bool LinuxInput::GetKeyDownImpl(KeyCode keyCode)
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int keyState = glfwGetKey(appWindow, keyCode);

		return keyState == GLFW_PRESS;
	}

	bool LinuxInput::GetKeyUpImpl(KeyCode keyCode)
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int keyState = glfwGetKey(appWindow, keyCode);

		return keyState == GLFW_RELEASE;
	}

	bool LinuxInput::GetMouseButtonDownImpl(MouseButton mouseButton)
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int mouseButtonState = glfwGetMouseButton(appWindow, mouseButton);

		return mouseButtonState == GLFW_PRESS;
	}

	bool LinuxInput::GetMouseButtonUpImpl(MouseButton mouseButton)
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int mouseButtonState = glfwGetMouseButton(appWindow, mouseButton);

		return mouseButtonState == GLFW_RELEASE;
	}

	glm::vec2 LinuxInput::GetMousePositionImpl()
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		double xPos, yPos;

		glfwGetCursorPos(appWindow, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float LinuxInput::GetMouseXImpl()
	{
		OPTICK_EVENT();

		return GetMousePosition().x;
	}

	float LinuxInput::GetMouseYImpl()
	{
		OPTICK_EVENT();

		return GetMousePosition().y;
	}

}