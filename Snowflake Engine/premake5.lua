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
		"Source/**.h",

		"%{IncludeDir.glm}/**.hpp",
		"%{IncludeDir.glm}/**.inl",

		"%{IncludeDir.stb_image}/*.cpp",
		"%{IncludeDir.stb_image}/*.h"
	}

	includedirs
	{
		"Source",
		"Source/Runtime",
		"Source/Runtime/Core",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	links
	{
		"spdlog",
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
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