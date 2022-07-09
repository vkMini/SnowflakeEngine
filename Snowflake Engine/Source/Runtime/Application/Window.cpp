#include "sfpch.h"
#include "Window.h"

#include "Core/Core.h"

#ifdef SNOWFLAKE_PLATFORM_WIN64
	#include "Windows/WindowsWindow.h"
#elif defined(SNOWFLAKE_PLATFORM_MACOS)
	#include "Mac/MacWindow.h"
#elif defined(SNOWFLAKE_PLATFORM_LINUX)
	#include "Linux/LinuxWindow.h"
#endif

#include "Utilities/PlatformUtils.h"

namespace Snowflake {

	Scope<Window> Window::CreateWindow(const WindowSpecification& specs)
	{
		switch (PlatformUtils::GetCurrentPlatform())
		{
			case PlatformUtils::OSPlatform::Windows:
			{
				#ifdef SNOWFLAKE_PLATFORM_WIN64
					return CreateScope<WindowsWindow>(specs);
				#endif
			}

			case PlatformUtils::OSPlatform::MacOS:
			{
				#ifdef SNOWFLAKE_PLATFORM_MACOS
					return CreateScope<MacWindow>(specs);
				#endif
			}

			case PlatformUtils::OSPlatform::Linux:
			{
				#ifdef SNOWFLAKE_PLATFORM_LINUX
					return CreateScope<LinuxWindow>(specs);
				#endif
			}
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to create window! Unknown platform detected!");
		return nullptr;
	}

}