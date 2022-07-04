#pragma once

#include "Event.h"

#include <sstream>

namespace Snowflake {

	class MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return m_MouseButton; }

		CLASS_EVENT_CATEGORY(MouseEventCategory | MouseButtonEventCategory | InputEventCategory)
	protected:
		MouseButtonEvent(const uint16_t mouseButton)
			: m_MouseButton(mouseButton) {}

		uint16_t m_MouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const uint16_t mouseButton)
			: MouseButtonEvent(mouseButton) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_MouseButton;
			return ss.str();
		}

		CLASS_EVENT_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(uint16_t mouseButton)
			: MouseButtonEvent(mouseButton) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_MouseButton;
			return ss.str();
		}

		CLASS_EVENT_TYPE(MouseButtonReleased)
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent (X: " << m_XOffset << ", Y: " << m_YOffset << ")";
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(MouseEventCategory | InputEventCategory)
		CLASS_EVENT_TYPE(MouseScrolled)
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float xPos, const float yPos)
			: m_XPos(xPos), m_YPos(yPos) {}

		float GetXPos() const { return m_XPos; }
		float GetYPos() const { return m_YPos; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent (X: " << m_XPos << ", Y: " << m_YPos << ")";
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(MouseEventCategory | InputEventCategory)
		CLASS_EVENT_TYPE(MouseMoved)
	private:
		float m_XPos, m_YPos;
	};
}