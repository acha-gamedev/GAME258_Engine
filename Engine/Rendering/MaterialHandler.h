#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>

struct Material {
	GLuint diffuseMap; //newmtl
	float shininess; //Ns
	float transparency; //d or Tr
	glm::vec3 ambientColour, specularColour, diffuseColour; // ambient: Ka, specular: Ks, diffuse: Kd
	inline Material() : diffuseMap(0), shininess(32.0f), transparency(1.0f),
		ambientColour(1.0f, 1.0f, 1.0f), specularColour(1.0f, 1.0f, 1.0f), diffuseColour(1.0f, 1.0f, 1.0f) {}
};

class MaterialHandler {
private:
	static std::unique_ptr<MaterialHandler> instance;
	friend std::default_delete<MaterialHandler>;

	static std::unordered_map<std::string, Material> materialList;

public:
	MaterialHandler(const MaterialHandler&) = delete;
	MaterialHandler(MaterialHandler&&) = delete;
	MaterialHandler& operator=(const MaterialHandler&) = delete;
	MaterialHandler& operator=(MaterialHandler&&) = delete;

	static MaterialHandler* GetInstance();
	void OnDestroy();

	void AddMaterial(std::string _name, Material _material);
	Material GetMaterial(std::string _name) const;
private:
	MaterialHandler();
	~MaterialHandler();
};

#endif //MATERIALHANDLER_H