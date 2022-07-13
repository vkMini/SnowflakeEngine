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

		virtual void SetInt(const std::string& name, int value) override;

		virtual void SetFloat4(const std::string& name, const glm::vec4& values) override;

		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override;
	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& shaderSource);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_ShaderProgram;
	};
}