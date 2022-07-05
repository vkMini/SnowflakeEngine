#pragma once

#include <map>

namespace Snowflake {

	class PlatformUtils
	{
	public:
		enum class OSPlatform
		{
			Unknown = 0,

			Windows, MacOS, Linux
		};

		static OSPlatform GetCurrentPlatform() { return m_CurrentPlatform; }
	private:
		static OSPlatform m_CurrentPlatform;
	};

	/*--------------------*/
	/* Operator Overloads */
	/*--------------------*/

	inline std::ostream& operator<<(std::ostream& os, const PlatformUtils::OSPlatform& platform)
	{
		static std::map<PlatformUtils::OSPlatform, std::string> platformStrings;

		platformStrings[PlatformUtils::OSPlatform::Unknown] = "Unknown";
		platformStrings[PlatformUtils::OSPlatform::Windows] = "Windows";
		platformStrings[PlatformUtils::OSPlatform::MacOS]   = "MacOS";
		platformStrings[PlatformUtils::OSPlatform::Linux]   = "Linux";
		
		return os << platformStrings[platform];
	}
}