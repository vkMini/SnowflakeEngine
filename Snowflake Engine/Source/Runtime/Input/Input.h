#pragma once

#include "Core/Core.h"

#include "InputCodes.h"

#include <glm/glm.hpp>

namespace Snowflake {

	class Input
	{
	public:
		static bool GetKeyDown(KeyCode keyCode) { return s_InputInstance->GetKeyDownImpl(keyCode); }
		static bool GetKeyUp(KeyCode keyCode) { return s_InputInstance->GetKeyUpImpl(keyCode); }

		static bool GetMouseButtonDown(MouseButton mouseButton) { return s_InputInstance->GetMouseButtonDownImpl(mouseButton); }
		static bool GetMouseButtonUp(MouseButton mouseButton) { return s_InputInstance->GetMouseButtonUpImpl(mouseButton); }

		static glm::vec2 GetMousePosition() { return s_InputInstance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_InputInstance->GetMouseXImpl(); }
		static float GetMouseY() { return s_InputInstance->GetMouseYImpl(); }
	protected:
		virtual bool GetKeyDownImpl(KeyCode keyCode) = 0;
		virtual bool GetKeyUpImpl(KeyCode keyCode) = 0;

		virtual bool GetMouseButtonDownImpl(MouseButton mouseButton) = 0;
		virtual bool GetMouseButtonUpImpl(MouseButton mouseButton) = 0;

		virtual glm::vec2 GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static void Initialize();

		static Ref<Input> s_InputInstance;

		// Friend application so it can access the Initialize method
		friend class Application;
	};
}
