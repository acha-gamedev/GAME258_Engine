#version 450 core

in vec3 Normal;
in vec2 TexCoord;
in vec3 Colour;

out vec4 fragColour;

void main() {
	fragColour = vec4(Colour, 1.0);
}