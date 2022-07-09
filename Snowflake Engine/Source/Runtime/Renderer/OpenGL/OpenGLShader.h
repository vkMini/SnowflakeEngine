#pragma once

#include "RendererCore/Shader.h"

typedef unsigned int GLenum;

namespace Snowflake {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& shaderSource);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_ShaderProgram;
	};
}