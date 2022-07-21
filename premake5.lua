include "Dependencies.lua"

workspace "Snowflake Engine"
	architecture "x86_64"
	startproject "Snowstorm"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

BinariesDir = "%{wks.location}/Binaries/%{prj.name}"
IntermediateDir = "!%{wks.location}/Intermediate/%{prj.name}"

-- Include Projects

group "Dependencies"
	include "Snowflake Engine/ThirdParty/spdlog"
	include "Snowflake Engine/ThirdParty/GLFW"
	include "Snowflake Engine/ThirdParty/Glad"
	include "Snowflake Engine/ThirdParty/ImGui"
	include "Snowflake Engine/ThirdParty/Optick"
group ""

group "Core"
	include "Snowflake Engine"
group ""

group "Tools"
	include "Snowstorm"
group ""

group "Misc"
	include "SandboxGame"
group ""
