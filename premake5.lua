workspace "Snowflake Engine"
	architecture "x86_64"
	startproject "SandboxGame"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

BinariesDir = "%{wks.location}/Binaries/%{prj.name}/Win64"
IntermediateDir = "!%{wks.location}/Intermediate/%{prj.name}"

include "Snowflake Engine"
include "SandboxGame"