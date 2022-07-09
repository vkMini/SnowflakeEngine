#include <Snowflake.h>

class SandboxLayer : public Snowflake::Layer
{
public:
	// Called when the layer is created or push
	void OnAttach() override
	{
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		unsigned int indices[3] = {
			0, 1, 2
		};

		m_Shader = Snowflake::Shader::CreateShader("Assets/Shaders/Default.glsl");

		m_VertexArray = Snowflake::VertexArray::CreateVertexArray();

		m_VertexBuffer = Snowflake::VertexBuffer::CreateBuffer(vertices, sizeof(vertices));
		m_VertexBuffer->SetBufferLayout({
			{ Snowflake::ShaderDataType::Float3, "a_Position" }
		});

		m_IndexBuffer = Snowflake::IndexBuffer::CreateBuffer(indices, sizeof(indices));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	}

	// Called when the layer is popped or destroyed
	void OnDetach() override
	{

	}

	// Called every frame
	void OnUpdate() override
	{
		Snowflake::RendererCommand::SetClearColor({ 0.45f, 0.55f, 0.60f, 1.0f });
		Snowflake::RendererCommand::Clear();

		Snowflake::Renderer::Submit(m_Shader, m_VertexArray);
	}
	
	// Called when an event is dispatched
	void OnEvent(Snowflake::Event& event) override
	{
		
	}
private:
	Snowflake::Ref<Snowflake::Shader> m_Shader;
	Snowflake::Ref<Snowflake::VertexBuffer> m_VertexBuffer;
	Snowflake::Ref<Snowflake::IndexBuffer> m_IndexBuffer;
	Snowflake::Ref<Snowflake::VertexArray> m_VertexArray;
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