project "Snowstorm"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    targetdir(BinariesDir)
    objdir(IntermediateDir)

    files
    {
        "Source/**.cpp",
        "Source/**.h"
    }

    includedirs
    {
        "%{wks.location}/Snowflake Engine/Source",
        "%{wks.location}/Snowflake Engine/Source/Runtime",
        "%{wks.location}/Snowflake Engine/Source/Runtime/Core",

        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Snowflake Engine"
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

    filter "configurations:Dist"
        kind "WindowedApp"
        entrypoint "mainCRTStartup"
        defines "SNOWFLAKE_DIST"
        runtime "Release"
        optimize "On"