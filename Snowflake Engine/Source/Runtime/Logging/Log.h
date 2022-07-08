#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

namespace Snowflake {

	class Log
	{
	public:
		static void Initialize();

		static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

/* Operator overloads for the glm types to make them printable */

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

// Macros for logging from the engine
#define SNOWFLAKE_ENGINE_TRACE(...) Snowflake::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define SNOWFLAKE_ENGINE_INFO(...)  Snowflake::Log::GetEngineLogger()->info(__VA_ARGS__)
#define SNOWFLAKE_ENGINE_DEBUG(...) Snowflake::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define SNOWFLAKE_ENGINE_WARN(...)  Snowflake::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define SNOWFLAKE_ENGINE_ERROR(...) Snowflake::Log::GetEngineLogger()->error(__VA_ARGS__)
#define SNOWFLAKE_ENGINE_FATAL(...) Snowflake::Log::GetEngineLogger()->critical(__VA_ARGS__)

// Macros for logging from the client
#define SNOWFLAKE_CLIENT_TRACE(...) Snowflake::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SNOWFLAKE_CLIENT_INFO(...)  Snowflake::Log::GetClientLogger()->info(__VA_ARGS__)
#define SNOWFLAKE_CLIENT_DEBUG(...) Snowflake::Log::GetClientLogger()->debug(__VA_ARGS__)
#define SNOWFLAKE_CLIENT_WARN(...)  Snowflake::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SNOWFLAKE_CLIENT_ERROR(...) Snowflake::Log::GetClientLogger()->error(__VA_ARGS__)
#define SNOWFLAKE_CLIENT_FATAL(...) Snowflake::Log::GetClientLogger()->critical(__VA_ARGS__)