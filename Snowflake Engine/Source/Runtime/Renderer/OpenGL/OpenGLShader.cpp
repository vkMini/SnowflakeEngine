#include "sfpch.h"
#include "OpenGLShader.h"

#include "Utilities/FileUtils.h"

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace Snowflake {

	static GLenum GetShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")					   return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		if (type == "geometry")					   return GL_GEOMETRY_SHADER;
		if (type == "compute")					   return GL_COMPUTE_SHADER;

		SNOWFLAKE_ENGINE_ASSERT(false, "Failed to get shader type for '" + type + "'!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string shaderSource = FileUtils::ReadAllLines(filepath);
		auto shaderSources = PreProcess(shaderSource);
		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderProgram);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_ShaderProgram);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	/* Uniform Uploading Functions */

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLint uniformLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform1i(uniformLocation, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint uniformLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform1iv(uniformLocation, count, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		GLint uniformLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform1f(uniformLocation, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint uniformLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform2f(uniformLocation, values.x, values.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint uniformLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform3f(uniformLocation, values.x, values.y, values.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint uniformLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniform4f(uniformLocation, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint uniformLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint uniformLocation = glGetUniformLocation(m_ShaderProgram, name.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	/*-----------------------------*/

	/*-----------------------------------------------------------------------------------------------------------------------------*/
	/* Used in compilation of shaders read from files. Credit to The Cherno for this method of shader pre-processing and compiling */
	/*-----------------------------------------------------------------------------------------------------------------------------*/

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& shaderSource)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = shaderSource.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = shaderSource.find_first_of("\r\n", pos);
			SNOWFLAKE_ENGINE_ASSERT(eol != std::string::npos, "Failed to pre-process shader! Syntax error!");

			size_t begin = pos + typeTokenLength + 1;
			std::string type = shaderSource.substr(begin, eol - begin);
			SNOWFLAKE_ENGINE_ASSERT(GetShaderTypeFromString(type), "Failed to pre-process shader! Invalid shader type specified!");

			size_t nextLinePos = shaderSource.find_first_not_of("\r\n", eol);
			pos = shaderSource.find(typeToken, nextLinePos);
			shaderSources[GetShaderTypeFromString(type)] = shaderSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSource.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint shaderProgram = glCreateProgram();
		SNOWFLAKE_ENGINE_ASSERT(shaderSources.size() <= 2, "Failed to compile shader! Only two shader types are allowed in one file!");

		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;

		for (auto& keyValue : shaderSources)
		{
			GLenum shaderType = keyValue.first;
			const std::string& shaderSource = keyValue.second;
			
			std::string shaderTypeStr;
			switch (shaderType)
			{
				case GL_VERTEX_SHADER:   shaderTypeStr = "vertex";   break;
				case GL_FRAGMENT_SHADER: shaderTypeStr = "fragment"; break;
				case GL_GEOMETRY_SHADER: shaderTypeStr = "geometry"; break;
				case GL_COMPUTE_SHADER:  shaderTypeStr = "compute";  break;
			}


			GLuint shader = glCreateShader(shaderType);

			const GLchar* shaderSourceCStr = shaderSource.c_str();
			glShaderSource(shader, 1, &shaderSourceCStr, nullptr);

			glCompileShader(shader);

			GLint isShaderCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isShaderCompiled);
			if (isShaderCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				SNOWFLAKE_ENGINE_ERROR("Failed to compile {} shader!", shaderTypeStr);
				SNOWFLAKE_ENGINE_ERROR("{}", infoLog.data());
				break;
			}

			glAttachShader(shaderProgram, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_ShaderProgram = shaderProgram;

		glLinkProgram(shaderProgram);

		GLint isShaderProgramLinked = 0;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int*)&isShaderProgramLinked);
		if (isShaderProgramLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

			SNOWFLAKE_ENGINE_ERROR("Failed to link shader program!");
			SNOWFLAKE_ENGINE_ERROR("{}", infoLog.data());
			return;
		}

		for (auto shaderID : glShaderIDs)
			glDetachShader(shaderProgram, shaderID);
	}

}