#include <Application/Application.h>
#include <Application/ApplicationEntryPoint.h>

#include "Editor/EditorLayer.h"

namespace Snowflake {

	class SnowstormApplication : public Application 
	{
	public:
		SnowstormApplication()
			: Application("Snowstorm")
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication()
	{
		return new SnowstormApplication();
	}

}