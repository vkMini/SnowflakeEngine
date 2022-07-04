#include <Snowflake.h>

class SandboxApp : public Snowflake::Application
{
public:
	SandboxApp()
	{

	}

	~SandboxApp()
	{

	}
};

Snowflake::Application* Snowflake::CreateApplication()
{
	return new SandboxApp();
}