#include "sfpch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <optick.h>

namespace Snowflake {

	static bool s_LoggersRegistered = false;

	std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Initialize()
	{
		OPTICK_EVENT();

		std::vector<spdlog::sink_ptr> loggerSinks;
		loggerSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		loggerSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Logs/Snowflake Engine.log", true));

		loggerSinks[0]->set_pattern("[%m-%d-%Y | %I:%M:%S] %^[%l] (%n): %v%$");
		loggerSinks[1]->set_pattern("[%m-%d-%Y | %I:%M:%S] %^[%l] (%n): %v%$");

		if (!s_LoggersRegistered)
		{
			s_EngineLogger = std::make_shared<spdlog::logger>("Snowflake Engine", begin(loggerSinks), end(loggerSinks));
			spdlog::register_logger(s_EngineLogger);
			s_EngineLogger->flush_on(spdlog::level::trace);
			s_EngineLogger->set_level(spdlog::level::trace);

			s_ClientLogger = std::make_shared<spdlog::logger>("Snowflake Application", begin(loggerSinks), end(loggerSinks));
			spdlog::register_logger(s_ClientLogger);
			s_ClientLogger->flush_on(spdlog::level::trace);
			s_ClientLogger->set_level(spdlog::level::trace);

			s_LoggersRegistered = true;
		}
	}
}