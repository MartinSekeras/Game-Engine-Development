#region Vertex
#version 440 core

layout(location = 0) in vec2 a_vertexPosition;
layout(location = 1) in vec2 a_texCoords;

out vec2 textCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	textCoords = vec2(a_texCoords);
	gl_Position = u_projection * u_view * u_model * vec4(a_vertexPosition, 1.0, 1.0);
}

#region Fragment
#version 440 core

layout(location = 0) out vec4 colour;
in vec2 textCoords;

uniform vec4 u_tint;
uniform sampler2D u_texData;

void main()
{
	colour = texture(u_texData, textCoords) * u_tint;
}