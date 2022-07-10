#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TextureCoord;

void main()
{
	v_TextureCoord = a_TextureCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 430 core

uniform sampler2D u_Texture;

in vec2 v_TextureCoord;

out vec4 FragColor;

void main()
{
	FragColor = texture(u_Texture, v_TextureCoord);
}