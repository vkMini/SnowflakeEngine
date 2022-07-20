#include "sfpch.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

#include <optick.h>

namespace Snowflake {

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		OPTICK_EVENT();

		glCreateBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		OPTICK_EVENT();

		glDeleteBuffers(1, &m_IndexBuffer);
	}

	void OpenGLIndexBuffer::Bind()
	{
		OPTICK_EVENT();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		OPTICK_EVENT();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}