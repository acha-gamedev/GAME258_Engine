#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H

#include <sstream>
#include <vector>
#include "../Rendering/MaterialHandler.h"
#include "../Rendering/TextureHandler.h"

class MaterialLoader {
public:
	MaterialLoader() = delete;
	MaterialLoader(const MaterialLoader&) = delete;
	MaterialLoader(MaterialLoader&&) = delete;
	MaterialLoader& operator=(const MaterialLoader&) = delete;
	MaterialLoader& operator=(MaterialLoader&&) = delete;

	~MaterialLoader();

	static void LoadMaterial(std::string filePath);
private:
	static GLuint LoadTexture(std::string name);
};

#endif //MATERIALLOADER_H