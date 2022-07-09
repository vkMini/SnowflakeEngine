#pragma once

namespace Snowflake {

	class FileUtils
	{
	public:
		static std::string ReadAllLines(const std::string& filepath);
	};
}