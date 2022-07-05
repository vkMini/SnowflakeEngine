#pragma once

#include "Event.h"

#include <sstream>

namespace Snowflake {

	class KeyboardEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_KeyCode; }

		CLASS_EVENT_CATEGORY(KeyboardEventCategory | InputEventCategory)
	protected:
		KeyboardEvent(const uint16_t keyCode)
			: m_KeyCode(keyCode) {}

		uint16_t m_KeyCode;
	};

	class KeyPressedEvent : public KeyboardEvent
	{
	public:
		KeyPressedEvent(const uint16_t keyCode, bool isRepeated = false)
			: KeyboardEvent(keyCode), m_IsRepeated(isRepeated) {}

		bool IsBeingRepeated() const { return m_IsRepeated; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (Repeated: " << m_IsRepeated << ")";
			return ss.str();
		}

		CLASS_EVENT_TYPE(KeyPressed)
	private:
		bool m_IsRepeated;
	};

	class KeyReleasedEvent : public KeyboardEvent
	{
	public:
		KeyReleasedEvent(const uint16_t keyCode)
			: KeyboardEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		CLASS_EVENT_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyboardEvent
	{
	public:
		KeyTypedEvent(const uint16_t keyCode)
			: KeyboardEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		CLASS_EVENT_TYPE(KeyTyped)
	};

}