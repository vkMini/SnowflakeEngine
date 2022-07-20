#pragma once

#ifdef SNOWFLAKE_PLATFORM_WIN64
	#undef CreateFile
	#undef WriteToFile
	#undef DeleteFile
#endif

namespace Snowflake {

	class FileUtils
	{
	public:
		static std::string ReadAllLines(const std::string& filepath);

		static void CreateFile(const std::string& filepath);
		static void WriteToFile(const std::string& filepath, const std::string& text);
		static void ExecuteFile(const std::string& filepath);
		static void DeleteFile(const std::string& filepath);
	};
}