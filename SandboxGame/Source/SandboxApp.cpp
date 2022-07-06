#include <Snowflake.h>

class SandboxLayer : public Snowflake::Layer
{
public:
	// Called when the layer is created or push
	void OnAttach() override
	{

	}

	// Called when the layer is popped or destroyed
	void OnDetach() override
	{

	}

	// Called every frame
	void OnUpdate() override
	{
		
	}

	// Called when an event is dispatched
	void OnEvent(Snowflake::Event& event) override
	{
		
	}
};

class SandboxApp : public Snowflake::Application
{
public:
	SandboxApp()
	{
		PushLayer(new SandboxLayer());
	}

	~SandboxApp()
	{

	}
};

Snowflake::Application* Snowflake::CreateApplication()
{
	return new SandboxApp();
}