#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;

out vec3 v_Position;

void main()
{
	v_Position = a_Position;
	gl_Position = u_ViewProjection * vec4(a_Position,1.0);
}

#type fragment
#version 430 core

in vec3 v_Position;

out vec4 FragColor;

void main()
{
	FragColor = vec4(v_Position + 0.5 * 0.5, 1.0);
}