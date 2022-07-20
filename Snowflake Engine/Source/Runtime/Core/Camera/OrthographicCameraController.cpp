#include "sfpch.h"
#include "OrthographicCameraController.h"

#include "Input/Input.h"

#include <optick.h>

namespace Snowflake {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool isRotatable)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotatable(isRotatable) {}

	void OrthographicCameraController::OnFixedUpdate(Time deltaTime)
	{
		OPTICK_EVENT();

		if (Input::GetKeyDown(KeyCode::A))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraMovementSpeed * deltaTime;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraMovementSpeed * deltaTime;
		}
		else if (Input::GetKeyDown(KeyCode::D))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraMovementSpeed * deltaTime;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraMovementSpeed * deltaTime;
		}

		if (Input::GetKeyDown(KeyCode::W))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraMovementSpeed * deltaTime;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraMovementSpeed * deltaTime;
		}
		else if (Input::GetKeyDown(KeyCode::S))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraMovementSpeed * deltaTime;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraMovementSpeed * deltaTime;
		}

		if (m_Rotatable)
		{
			if (Input::GetKeyDown(KeyCode::Q))
				m_CameraRotation += m_CameraRotationSpeed * deltaTime;

			if (Input::GetKeyDown(KeyCode::E))
				m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraMovementSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(SNOWFLAKE_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SNOWFLAKE_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

}