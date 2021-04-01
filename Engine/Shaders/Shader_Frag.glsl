#version 450 core

struct Light {
	vec3 position;
	float ambient;
	float diffuse;
	float specular;
	vec3 colour;
};

struct Material {
	sampler2D texture;
	float shininess;
	float transparency;
	vec3 ambiColour;
	vec3 diffColour;
	vec3 specColour;
};

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

uniform vec3 cameraPos;
uniform Light light;
uniform Material mat;

out vec4 fragColour;

void main() {
	//Ambient
	vec3 ambient = light.ambient * mat.ambiColour * texture(mat.texture, TexCoord).rgb * light.colour;
	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = (diff * mat.diffColour) * texture(mat.texture, TexCoord).rgb * light.colour;
	//Specular
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), mat.shininess);
	vec3 specular = (spec * mat.specColour) * light.colour;
	//Combined
	vec3 result = ambient + diffuse + specular;
	fragColour = vec4(result, mat.transparency);
}