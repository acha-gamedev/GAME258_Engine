#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normalIn;
layout (location = 2) in vec2 uvCoord;
layout (location = 3) in vec3 rgbValue;

out vec3 Normal;
out vec2 TexCoord;
out vec3 Colour;

void main() {
	gl_Position = vec4(position, 1.0f);
	Colour = rgbValue;
}