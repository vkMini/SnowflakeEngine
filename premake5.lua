include "Dependencies.lua"

workspace "Snowflake Engine"
	architecture "x86_64"
	startproject "SandboxGame"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

BinariesDir = "%{wks.location}/Binaries/%{prj.name}"
IntermediateDir = "!%{wks.location}/Intermediate/%{prj.name}"

-- Include Projects

group "Dependencies"
	include "Snowflake Engine/ThirdParty/spdlog"
	include "Snowflake Engine/ThirdParty/GLFW"
	include "Snowflake Engine/ThirdParty/Glad"
	include "Snowflake Engine/ThirdParty/ImGui"
group ""

group "Core"
	include "Snowflake Engine"
group ""

group "Tools"
	include "SandboxGame"
group ""
