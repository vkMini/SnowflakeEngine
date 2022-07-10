#pragma once

#include "Time/Time.h"

#include "Events/Event.h"

namespace Snowflake {

	class Layer
	{
	public:
		Layer(const std::string& layerName = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		/* These update functions are meant to be similar to Unity's Update, FixedUpdate and LateUpdate functions. */
		virtual void OnUpdate() {}
		virtual void OnFixedUpdate(Time deltaTime) {}
		virtual void OnLateUpdate() {}
		/*----------------------------------------------------------------------------------------------------------*/

		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_LayerName; }
	private:
		std::string m_LayerName;
	};
}