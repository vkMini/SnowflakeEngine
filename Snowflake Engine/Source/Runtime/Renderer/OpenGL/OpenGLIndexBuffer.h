#pragma once

#include "RendererCore/IndexBuffer.h"

namespace Snowflake {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual const uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_Count;
		uint32_t m_IndexBuffer;
	};
}