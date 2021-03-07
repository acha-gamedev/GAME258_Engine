#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normalIn;
layout (location = 2) in vec2 uvCoord;
layout (location = 3) in vec3 rgbValue;

out vec3 Normal;
out vec2 TexCoord;
out vec3 Colour;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(position, 1.0f);
	Colour = rgbValue;
	TexCoord = uvCoord;
	Normal = (inverse(transpose(model)) * vec4(normalIn, 1.0f)).xyz;
	FragPos = (model * vec4(position, 1.0f)).xyz;
}