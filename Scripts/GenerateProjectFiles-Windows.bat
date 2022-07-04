@echo off

echo Generating Project Files...

cd ..\

call "Snowflake Engine"\ThirdParty\Premake\premake5.exe xcode4
PAUSE