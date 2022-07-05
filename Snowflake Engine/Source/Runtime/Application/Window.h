#pragma once

#include "Core/Core.h"

#include "Events/Event.h"

// On Windows, undefine the CreateWindow macro from the Win32 API so it can be used as a function name
#ifdef SNOWFLAKE_PLATFORM_WIN64
	#undef CreateWindow
#endif

namespace Snowflake {

	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width, Height;
		bool VSync, Fullscreen, Maximized, Resizable;

		WindowSpecification(uint32_t width = 1600, 
							uint32_t height = 900, 
							const std::string & title = "Snowflake Engine", 
							bool vSync = true, 
							bool fullscreen = false, 
							bool maximized = false,
							bool resizable = true)
			: Width(width), Height(height), Title(title), VSync(vSync), Fullscreen(fullscreen), Maximized(maximized), Resizable(resizable) {}
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		using EventCallbackFunction = std::function<void(Event&)>;

		virtual void Initialize() = 0;
		virtual void ProcessEvents() = 0;
		virtual void SwapBuffers() = 0;

		inline virtual uint32_t GetWidth() const = 0;
		inline virtual uint32_t GetHeight() const = 0;

		virtual std::pair<uint32_t, uint32_t> GetSize() const = 0;
		virtual std::pair<uint32_t, uint32_t> GetPosition() const = 0;

		/* Window attributes */

		virtual void SetEventCallbackFunction(const EventCallbackFunction& eventFunction) = 0;
		
		virtual bool IsVSyncEnabled() = 0;
		virtual void SetVSyncEnabled(bool isEnabled) = 0;

		virtual bool IsResizable() = 0;
		virtual void SetResizable(bool isResizable) = 0;

		virtual void Maximize() = 0;
		virtual void CenterWindow() = 0;

		virtual const std::string& GetTitle() const = 0;
		virtual void SetTitle(const std::string& title) = 0;

		inline virtual void* GetWindowHandle() const = 0;

		static Scope<Window> CreateWindow(const WindowSpecification& specification = WindowSpecification());
	};
}
