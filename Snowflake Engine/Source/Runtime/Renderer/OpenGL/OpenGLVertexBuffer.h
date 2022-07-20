#pragma once

#include "RendererCore/VertexBuffer.h"

namespace Snowflake {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetBufferLayout() const override { return m_BufferLayout; };
		virtual void SetBufferLayout(const BufferLayout& bufferLayout) override { m_BufferLayout = bufferLayout; }
	private:
		BufferLayout m_BufferLayout;
		uint32_t m_VertexBuffer;
	};
}