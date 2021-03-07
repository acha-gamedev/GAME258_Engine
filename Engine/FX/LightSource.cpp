#include "LightSource.h"

LightSource::LightSource(glm::vec3 _position, float _ambient, float _diffuse, float _specular, glm::vec3 _rgbColour) :
	position(_position), ambient(_ambient), diffuse(_diffuse), specular(_specular), rgbColour(_rgbColour) {}

LightSource::~LightSource() {}