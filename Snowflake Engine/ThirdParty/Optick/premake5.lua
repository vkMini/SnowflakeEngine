project "Optick"
	kind "StaticLib"
	language "C++"
	staticruntime "Off"

	targetdir("Binaries")
	objdir("!Intermediate")

	files
	{
		"src/optick.config.h",
		"src/optick.h",
		"src/optick_capi.cpp",
		"src/optick_capi.h",
		"src/optick_common.h",
		"src/optick_core.cpp",
		"src/optick_core.h",
		"src/optick_core.platform.h",
		"src/optick_gpu.cpp",
		"src/optick_gpu.h",
		"src/optick_memory.h",
		"src/optick_message.cpp",
		"src/optick_message.h",
		"src/optick_miniz.cpp",
		"src/optick_miniz.h",
		"src/optick_serialization.cpp",
		"src/optick_serialization.h",
		"src/optick_server.cpp",
		"src/optick_server.h",

		"include/*.h"
	}

	-- TODO: Remove this when then engine supports Vulkan
	removefiles
	{
		"src/optick_gpu.vulkan.cpp"
	}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"src/optick_core.win.h",
			"src/optick_gpu.d3d12.cpp"
		}

	filter "system:macosx"
		files
		{
			"src/optick_core.macos.h"
		}

	filter "system:linux"
		files
		{
			"src/optick_core.freebsd.h",
			"src/optick_core.linux.h",
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"