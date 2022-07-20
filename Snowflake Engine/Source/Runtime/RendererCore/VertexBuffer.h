#pragma once

#include "Core/Core.h"

#include "BufferLayout.h"

namespace Snowflake {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetBufferLayout() const = 0;
		virtual void SetBufferLayout(const BufferLayout& bufferLayout) = 0;

		static Ref<VertexBuffer> CreateBuffer(float* vertices, uint32_t size);
		static Ref<VertexBuffer> CreateBuffer(uint32_t size);
	};
}