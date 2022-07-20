#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoord;

uniform mat4 u_ViewProjection;

out vec2 v_TextureCoord;
out vec4 v_Color;

void main()
{
	v_TextureCoord = a_TextureCoord;
	v_Color = a_Color;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

uniform float u_TilingFactor;
uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 v_TextureCoord;
in vec4 v_Color;

out vec4 FragColor;

void main()
{
	// TODO: Uncomment when texture batching is supported
	// FragColor = texture(u_Texture, v_TextureCoord * u_TilingFactor) * u_Color;

	FragColor = v_Color;
}