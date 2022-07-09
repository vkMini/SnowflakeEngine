#include "sfpch.h"
#include "FileUtils.h"

#include "Core/Core.h"

#include <fstream>

namespace Snowflake {

	std::string FileUtils::ReadAllLines(const std::string& filepath)
	{
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

}