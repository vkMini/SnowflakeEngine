#include "sfpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Snowflake {

	static GLenum ConvertShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Snowflake::ShaderDataType::Float:    return GL_FLOAT;
		case Snowflake::ShaderDataType::Float2:   return GL_FLOAT;
		case Snowflake::ShaderDataType::Float3:   return GL_FLOAT;
		case Snowflake::ShaderDataType::Float4:   return GL_FLOAT;
		case Snowflake::ShaderDataType::Mat3:     return GL_FLOAT;
		case Snowflake::ShaderDataType::Mat4:     return GL_FLOAT;
		case Snowflake::ShaderDataType::Int:      return GL_INT;
		case Snowflake::ShaderDataType::Int2:     return GL_INT;
		case Snowflake::ShaderDataType::Int3:     return GL_INT;
		case Snowflake::ShaderDataType::Int4:     return GL_INT;
		case Snowflake::ShaderDataType::Bool:     return GL_BOOL;
		}

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to convert shader data type to OpenGL base type!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArray);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArray);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		SNOWFLAKE_ENGINE_ASSERT(vertexBuffer->GetBufferLayout().GetElements().size(), "Failed to add vertex buffer! It has no layout!");

		glBindVertexArray(m_VertexArray);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetBufferLayout();
		for (const auto& element : layout)
		{
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ConvertShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			glEnableVertexAttribArray(m_VertexBufferIndex);

			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_VertexArray);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}