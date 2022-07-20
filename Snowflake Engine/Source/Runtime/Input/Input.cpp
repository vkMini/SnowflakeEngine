#include "sfpch.h"
#include "Input.h"

#ifdef SNOWFLAKE_PLATFORM_WIN64
	#include "Windows/WindowsInput.h"
#elif defined(SNOWFLAKE_PLATFORM_MACOS)
	#include "Mac/MacInput.h"
#elif defined(SNOWFLAKE_PLATFORM_LINUX)
	#include "Linux/LinuxInput.h"	
#endif

#include "Utilities/PlatformUtils.h"

namespace Snowflake {

	Ref<Input> Input::s_InputInstance = nullptr;

	void Input::Initialize()
	{
		switch (PlatformUtils::GetCurrentPlatform())
		{
			case PlatformUtils::OSPlatform::Windows:
			{
				#ifdef SNOWFLAKE_PLATFORM_WIN64
					s_InputInstance = CreateRef<WindowsInput>();
				#endif

				break;
			}

			case PlatformUtils::OSPlatform::MacOS:
			{
				#ifdef SNOWFLAKE_PLATFORM_MACOS
					s_InputInstance = CreateRef<MacInput>();
				#endif

				break;
			}

			case PlatformUtils::OSPlatform::Linux:
			{
				#ifdef SNOWFLAKE_PLATFORM_LINUX
					s_InputInstance = CreateRef<LinuxInput>();
				#endif

				break;
			}
		}

		SNOWFLAKE_ENGINE_ASSERT(s_InputInstance, "Failed to create input instance! Unknown platform detected!");
	}

}