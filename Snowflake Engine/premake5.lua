project "Snowflake Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir(BinariesDir)
	objdir(IntermediateDir)

	pchsource "Source/sfpch.cpp"
	pchheader "sfpch.h"

	files
	{
		"Source/**.cpp",
		"Source/**.h"
	}

	includedirs
	{
		"Source",
		"Source/Runtime",

		"%{IncludeDir.spdlog}"
	}

	links
	{
		"spdlog"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SNOWFLAKE_PLATFORM_WIN64"
		}

	filter "system:macosx"
		defines
		{
			"SNOWFLAKE_PLATFORM_MACOS"
		}

	filter "system:linux"
		defines
		{
			"SNOWFLAKE_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "SNOWFLAKE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SNOWFLAKE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Release"
		defines "SNOWFLAKE_RELEASE"
		runtime "Release"
		optimize "Off"