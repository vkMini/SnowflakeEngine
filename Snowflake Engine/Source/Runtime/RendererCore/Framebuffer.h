#pragma once

#include "Core/Core.h"

namespace Snowflake {

	// TODO: FramebufferFormat
	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual const FramebufferSpecification& GetSpecification() const = 0;

		virtual uint32_t GetColorAttachmentHandle() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<Framebuffer> CreateFramebuffer(const FramebufferSpecification& specification);
	};
}
