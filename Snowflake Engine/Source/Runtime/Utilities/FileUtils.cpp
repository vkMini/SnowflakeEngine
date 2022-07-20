#include "sfpch.h"
#include "FileUtils.h"

#include "Core/Core.h"

#include "PlatformUtils.h"

#include <optick.h>

#include <fstream>
#include <filesystem>

namespace Snowflake {

	std::string FileUtils::ReadAllLines(const std::string& filepath)
	{
		OPTICK_EVENT();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else // if (size != -1)
			{
				SNOWFLAKE_ENGINE_ERROR("Failed to read file '{}'", filepath);
			}
		}
		else // if (in)
		{
			SNOWFLAKE_ENGINE_ERROR("Failed to open file '{}'", filepath);
		}

		return result;
	}

	/* Originally used in something else and aren't being used anymore, but are being kept due to be being useful functions to have in the engine's API */

	void FileUtils::CreateFile(const std::string& filepath)
	{
		OPTICK_EVENT();

		std::ofstream file;
		file.open(filepath);
		file.close();
	}

	void FileUtils::WriteToFile(const std::string& filepath, const std::string& text)
	{
		OPTICK_EVENT();

		std::ofstream file;
		file.open(filepath);

		file << text;

		file.close();
	}

	void FileUtils::ExecuteFile(const std::string& filepath)
	{
		OPTICK_EVENT();

		auto currentPlatform = PlatformUtils::GetCurrentPlatform();

		if (currentPlatform == PlatformUtils::OSPlatform::Windows)
		{
			system(filepath.c_str());
		}
		else if (currentPlatform == PlatformUtils::OSPlatform::MacOS || currentPlatform == PlatformUtils::OSPlatform::Linux)
		{
			std::string runCommand = "./" + filepath;
			system(runCommand.c_str());
		}

	}

	void FileUtils::DeleteFile(const std::string& filepath)
	{
		OPTICK_EVENT();

		if (std::filesystem::remove(filepath))
			SNOWFLAKE_ENGINE_INFO("Successfully deleted file '{}'", filepath);
		else
			SNOWFLAKE_ENGINE_ERROR("Failed to delete file '{}'", filepath);
	}

}