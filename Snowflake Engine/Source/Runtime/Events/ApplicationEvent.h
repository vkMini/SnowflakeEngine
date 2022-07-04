#pragma once

#include "Event.h"

#include <sstream>

namespace Snowflake {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		CLASS_EVENT_CATEGORY(ApplicationEventCategory)
		CLASS_EVENT_TYPE(WindowClose)
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent(const int focused)
			: m_Focused(focused) {}

		bool IsFocused() const { return m_Focused == 1 ? true : false; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowFocusEvent: " << IsFocused();
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(ApplicationEventCategory)
		CLASS_EVENT_TYPE(WindowFocus)
	private:
		int m_Focused;
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent(const int focused)
			: m_Focused(focused) {}

		bool IsFocusLost() const { return m_Focused == 0 ? true : false; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowLostFocusEvent: " << IsFocusLost();
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(ApplicationEventCategory)
		CLASS_EVENT_TYPE(WindowLostFocus)
	private:
		int m_Focused;
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent (Width: " << m_Width << ", Height: " << m_Height << ")";
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(ApplicationEventCategory)
		CLASS_EVENT_TYPE(WindowResize)
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(const int xPos, const int yPos)
			: m_XPos(xPos), m_YPos(yPos) {}

		int GetXPos() const { return m_XPos; }
		int GetYPos() const { return m_YPos; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMovedEvent (X: " << m_XPos << ", Y: " << m_YPos << ")";
			return ss.str();
		}

		CLASS_EVENT_CATEGORY(ApplicationEventCategory)
		CLASS_EVENT_TYPE(WindowMoved)
	private:
		int m_XPos, m_YPos;
	};
}