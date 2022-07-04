#pragma once

bool bIsApplicationRunning = true;

extern Snowflake::Application* Snowflake::CreateApplication();

namespace Snowflake {

	int Main(int argc, char** argv)
	{
		while (bIsApplicationRunning)
		{
			Application* app = CreateApplication();
			app->Start();
			delete app;
		}

		return 0;
	}
}

int main(int argc, char** argv)
{
	return Snowflake::Main(argc, argv);
}