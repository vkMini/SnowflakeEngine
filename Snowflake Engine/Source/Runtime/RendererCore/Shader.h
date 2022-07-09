#pragma once

#include "Core/Core.h"

namespace Snowflake {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Ref<Shader> CreateShader(const std::string& filepath);
	};

}