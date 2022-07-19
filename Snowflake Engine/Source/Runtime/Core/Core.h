#pragma once

#include "Logging/Log.h"

#include <memory>

#ifdef SNOWFLAKE_DEBUG
	#if defined(SNOWFLAKE_PLATFORM_WIN64)
		#define SNOWFLAKE_DEBUGBREAK() __debugbreak()
	#elif defined(SNOWFLAKE_PLATFORM_MACOS) || defined(SNOWFLAKE_PLATFORM_LINUX)
		#include <signal.h>
		#define SNOWFLAKE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Failed to enable debugbreak! The current platform doesn't support it yet!'"
	#endif
	
	#define SNOWFLAKE_ENABLE_ASSERTS
#else
	#define SNOWFLAKE_DEBUGBREAK()
#endif

#ifdef SNOWFLAKE_ENABLE_ASSERTS
	#define SNOWFLAKE_ENGINE_ASSERT(cond, ...) { if (!(cond)) { SNOWFLAKE_ENGINE_ERROR("Assertion Failed: {}", __VA_ARGS__);  SNOWFLAKE_DEBUGBREAK(); } }
	#define SNOWFLAKE_CLIENT_ASSERT(cond, ...) { if (!(cond)) { SNOWFLAKE_CLIENT_ERROR("Assertion Failed: {}", __VA_ARGS__);  SNOWFLAKE_DEBUGBREAK(); } }
#else
	#define SNOWFLAKE_ENGINE_ASSERT(cond, ...)
	#define SNOWFLAKE_CLIENT_ASSERT(cond, ...)
#endif

#define SNOWFLAKE_BIND_EVENT_FUNCTION(function) [this](auto&&... args) -> decltype(auto) { return this->function(std::forward<decltype(args)>(args)...); }

namespace Snowflake {

	// Refs
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	// Scopes 
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}