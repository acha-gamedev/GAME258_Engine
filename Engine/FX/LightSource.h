#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

class LightSource {
private:
	glm::vec3 position, rgbColour;
	float ambient, diffuse, specular;
public:
	LightSource(glm::vec3 _position, float _ambient, float _diffuse, float _specular, glm::vec3 _rgbColour);
	~LightSource();

	inline glm::vec3 GetPosition() const { return position; }
	inline glm::vec3 GetColour() const { return rgbColour; }
	inline float GetAmbient() const { return ambient; }
	inline float GetDiffuse() const { return diffuse; }
	inline float GetSpecular() const { return specular; }
};

#endif //LIGHTSOURCE_H