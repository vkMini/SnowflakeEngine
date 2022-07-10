#pragma once

#include "Time/Time.h"

#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

#include "OrthographicCamera.h"

namespace Snowflake {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool isRotatable = false);

		void OnFixedUpdate(Time deltaTime);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		bool m_Rotatable;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraMovementSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

		OrthographicCamera m_Camera;
	};

}
