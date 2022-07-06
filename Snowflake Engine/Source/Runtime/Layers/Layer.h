#pragma once

#include "Events/Event.h"

namespace Snowflake {

	class Layer
	{
	public:
		Layer(const std::string& layerName = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_LayerName; }
	private:
		std::string m_LayerName;
	};
}