#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 aTextureProjection;

out vec2 textureProjection;

uniform mat4 projection;

void main() {
	gl_Position = projection * vec4(vertexPos, 1);
	textureProjection = aTextureProjection;
}