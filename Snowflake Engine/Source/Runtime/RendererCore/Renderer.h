#pragma once

#include "RendererAPI.h"

#include "Shader.h"
#include "VertexArray.h"

#include "Camera/OrthographicCamera.h"

namespace Snowflake {

	class Renderer
	{
	public:
		static void Initialize();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& orthographicCamera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}
