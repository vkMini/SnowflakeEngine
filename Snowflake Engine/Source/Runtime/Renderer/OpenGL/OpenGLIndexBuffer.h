#pragma once

#include "RendererCore/IndexBuffer.h"

namespace Snowflake {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t m_IndexBuffer;
	};
}