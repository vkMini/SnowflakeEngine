#include "sfpch.h"
#include "WindowsInput.h"

#include "Application/Application.h"

#include <GLFW/glfw3.h>

#include <optick.h>

namespace Snowflake {

	bool WindowsInput::GetKeyDownImpl(KeyCode keyCode)
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int keyState = glfwGetKey(appWindow, keyCode);

		return keyState == GLFW_PRESS;
	}

	bool WindowsInput::GetKeyUpImpl(KeyCode keyCode)
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int keyState = glfwGetKey(appWindow, keyCode);

		return keyState == GLFW_RELEASE;
	}

	bool WindowsInput::GetMouseButtonDownImpl(MouseButton mouseButton)
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int mouseButtonState = glfwGetMouseButton(appWindow, mouseButton);

		return mouseButtonState == GLFW_PRESS;
	}

	bool WindowsInput::GetMouseButtonUpImpl(MouseButton mouseButton)
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		int mouseButtonState = glfwGetMouseButton(appWindow, mouseButton);

		return mouseButtonState == GLFW_RELEASE;
	}

	glm::vec2 WindowsInput::GetMousePositionImpl()
	{
		OPTICK_EVENT();

		auto appWindow = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetWindowHandle());
		double xPos, yPos;

		glfwGetCursorPos(appWindow, &xPos, &yPos);

		return { (float) xPos, (float) yPos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		OPTICK_EVENT();

		return GetMousePosition().x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		return GetMousePosition().y;
	}

}