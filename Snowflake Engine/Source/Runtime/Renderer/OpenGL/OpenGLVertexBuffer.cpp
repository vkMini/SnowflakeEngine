#include "sfpch.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

#include <optick.h>

namespace Snowflake {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		OPTICK_EVENT();

		glCreateBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		OPTICK_EVENT();

		glDeleteBuffers(1, &m_VertexBuffer);
	}

	void OpenGLVertexBuffer::Bind()
	{
		OPTICK_EVENT();

		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		OPTICK_EVENT();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}