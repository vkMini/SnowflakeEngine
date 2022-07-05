project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "Off"

    targetdir("Binaries")
    objdir("!Intermediate")

    files
    {
        "src/context.c",
        "src/init.c",
        "src/input.c",
        "src/internal.h",
        "src/mappings.h",
        "src/monitor.c",
        "src/platform.c",
        "src/platform.h",
        "src/window.c",

		"src/null_init.c",
		"src/null_joystick.c",
		"src/null_monitor.c",
		"src/null_window.c",

		"src/platform.c",
		"src/vulkan.c",
		"src/window.c",

        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"

        files
        {
            "src/win32_init.c",
            "src/win32_joystick.c",
            "src/win32_joystick.h",
            "src/win32_module.c",
            "src/win32_monitor.c",
            "src/win32_platform.h",
            "src/win32_thread.c",
            "src/win32_time.c",
            "src/win32_time.h",
            "src/win32_window.c",
            "src/wgl_context.c",
            "src/egl_context.c",
            "src/osmesa_context.c"
        }
        
        defines
        {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        links
        {
            "Dwmapi.lib"
        }

    filter "system:macosx"
        files
        {
            "src/cocoa_init.m",
            "src/cocoa_joystick.h",
            "src/cocoa_joystick.m",
            "src/cocoa_monitor.m",
            "src/cocoa_platform.h",
            "src/cocoa_time.c",
            "src/cocoa_time.h",
            "src/cocoa_window.m",
            "src/nsgl_context.m"
        }

        defines
        {
            "_GLFW_COCOA"
        }

    filter "system:linux"
        files
        {
            "src/linux_joystick.c",
            "src/linux_joystick.h",

            "src/posix_module.c",
            "src/posix_poll.c",
            "src/posix_thread.c",
            "src/posix_thread.h",
            "src/posix_time.c",
            "src/posix_time.h",

            "src/wl_init.c",
            "src/wl_monitor.c",
            "src/wl_platform.h",
            "src/wl_window.c",

            "src/x11_init.c",
            "src/x11_monitor.c",
            "src/x11_platform.h",
            "src/x11_window.c",
            "src/xkb_unicode.c",
            "src/xkb_unicode.h"
        }

        defines
        {
            "_GLFW_X11",
            "_GLFW_WAYLAND"
        }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"