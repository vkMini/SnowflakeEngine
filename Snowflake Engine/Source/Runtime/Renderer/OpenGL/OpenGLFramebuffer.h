#pragma once

#include "RendererCore/Framebuffer.h"

namespace Snowflake {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& specification);
		virtual ~OpenGLFramebuffer();

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; };

		virtual uint32_t GetColorAttachmentHandle() const override { return m_ColorAttachment; }

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void InvalidateFramebuffer();
	private:
		FramebufferSpecification m_Specification;

		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		uint32_t m_FramebufferID = 0;
	};
}