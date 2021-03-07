#version 450 core

struct Light {
	vec3 position;
	float ambient;
	float diffuse;
	float specular;
	vec3 colour;
};

in vec3 Normal;
in vec2 TexCoord;
in vec3 Colour;
in vec3 FragPos;

uniform sampler2D inputTexture;
uniform vec3 cameraPos;
uniform Light light;

out vec4 fragColour;

void main() {

	vec3 ambient = light.ambient * texture(inputTexture, TexCoord).rgb * light.colour;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = (diff * light.diffuse) * texture(inputTexture, TexCoord).rgb * light.colour;

	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = (spec * light.specular) * light.colour;

	vec3 result = ambient + diffuse + specular;
	fragColour = vec4(result, 1.0f);
}