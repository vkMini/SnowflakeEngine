#pragma once

#include "Layers/Layer.h"

namespace Snowflake {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		void SetDarkColorsTheme();
	};
}
