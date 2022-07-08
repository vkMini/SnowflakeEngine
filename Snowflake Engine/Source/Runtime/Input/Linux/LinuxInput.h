#pragma once

#include "Input/Input.h"

namespace Snowflake {

	class LinuxInput : public Input
	{
	public:
		virtual bool GetKeyDownImpl(KeyCode keyCode) override;
		virtual bool GetKeyUpImpl(KeyCode keyCode) override;

		virtual bool GetMouseButtonDownImpl(MouseButton mouseButton) override;
		virtual bool GetMouseButtonUpImpl(MouseButton mouseButton) override;

		virtual glm::vec2 GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}
