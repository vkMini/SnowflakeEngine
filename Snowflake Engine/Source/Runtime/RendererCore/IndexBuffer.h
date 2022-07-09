#pragma once

#include "Core/Core.h"

namespace Snowflake {

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Ref<IndexBuffer> CreateBuffer(uint32_t* indices, uint32_t size);
	};
}