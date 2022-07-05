#include "sfpch.h"
#include "PlatformUtils.h"

namespace Snowflake {

	#ifdef SNOWFLAKE_PLATFORM_WIN64
		PlatformUtils::OSPlatform PlatformUtils::m_CurrentPlatform = OSPlatform::Windows;
	#elif defined(SNOWFLAKE_PLATFORM_MACOS)
		PlatformUtils::OSPlatform PlatformUtils::m_CurrentPlatform = OSPlatform::MacOS;
	#elif defined(SNOWFLAKE_PLATFORM_LINUX)
		PlatformUtils::OSPlatform PlatformUtils::m_CurrentPlatform = OSPlatform::Linux;
	#else
		PlatformUtils::OSPlatform PlatformUtils::m_CurrentPlatform = OSPlatform::Unknown;
	#endif

}