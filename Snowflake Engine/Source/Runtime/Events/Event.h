#pragma once

#include <functional>

namespace Snowflake {

	enum class EventType
	{
		None = 0,

		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved,
		WindowClose, WindowFocus, WindowLostFocus, WindowResize, WindowMoved
	};

	enum EventCategory
	{
		None = 0,

		ApplicationEventCategory = (1 << (0)),
		InputEventCategory       = (1 << (1)),
		KeyboardEventCategory    = (1 << (2)),
		MouseEventCategory       = (1 << (3)),
		MouseButtonEventCategory = (1 << (4))
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		bool isHandled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory eventCategory)
		{
			return GetCategoryFlags() & eventCategory;
		}
	};

#define CLASS_EVENT_TYPE(event_type) static EventType GetStaticType() { return EventType::event_type; }\
									 virtual EventType GetEventType() const override { return GetStaticType(); }\
									 virtual const char* GetName() const override { return #event_type; }

#define CLASS_EVENT_CATEGORY(event_category) virtual int GetCategoryFlags() const override { return event_category; }

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		// F will be automatically deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& eventFunction)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.isHandled |= eventFunction(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}
}