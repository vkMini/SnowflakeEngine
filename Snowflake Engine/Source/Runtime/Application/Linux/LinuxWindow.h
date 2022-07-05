#pragma once

#include "Application/Window.h"

#include <GLFW/glfw3.h>

namespace Snowflake {

	class LinuxWindow : public Window
	{
	public:
		LinuxWindow(const WindowSpecification& specs);
		virtual ~LinuxWindow();

		virtual void Initialize() override;
		virtual void ProcessEvents() override;
		virtual void SwapBuffers() override;

		inline virtual uint32_t GetWidth() const override { return m_WindowData.Width; }
		inline virtual uint32_t GetHeight() const override { return m_WindowData.Height; }

		virtual std::pair<uint32_t, uint32_t> GetSize() const override { return { m_WindowData.Width, m_WindowData.Height }; }
		virtual std::pair<uint32_t, uint32_t> GetPosition() const override;

		/* Window attributes */

		virtual void SetEventCallbackFunction(const EventCallbackFunction& eventFunction) override { m_WindowData.EventCallback = eventFunction; }

		virtual bool IsVSyncEnabled() override { return m_WindowData.VSync; }
		virtual void SetVSyncEnabled(bool isEnabled) override;

		virtual bool IsResizable() override { return m_WindowData.Resizable; }
		virtual void SetResizable(bool isResizable) override;

		virtual void Maximize() override;
		virtual void CenterWindow() override;

		virtual const std::string& GetTitle() const override { return m_WindowData.Title; }
		virtual void SetTitle(const std::string& title) override;

		inline virtual void* GetWindowHandle() const override { return m_WindowHandle; };
	private:
		virtual void Shutdown();
	private:
		WindowSpecification m_Specification;
		GLFWwindow* m_WindowHandle;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync, Fullscreen, Resizable;

			EventCallbackFunction EventCallback;
		};

		WindowData m_WindowData;
	};
}
