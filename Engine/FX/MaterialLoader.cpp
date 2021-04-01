#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() {}

void MaterialLoader::LoadMaterial(std::string filePath) {
	std::ifstream file(filePath.c_str(), std::ios::in);
	if (!file) {
		Debug::LogError("Could not open mtl file " + filePath, "Engine/FX/MaterialLoader.cpp", __LINE__);
		return;
	}

	Material temp;
	std::string name;
	std::string line;
	while (std::getline(file, line)) {
		//Test for seperator "newmtl "
		if (line.substr(0, 7) == "newmtl ") {
			if (temp.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(name, temp);
				temp = Material();
			}
			name = line.substr(7);
			temp.diffuseMap = LoadTexture(name);
		}
		//Test for ambient colour "Ka "
		else if (line.substr(0, 4) == "\tKa ") {
			std::stringstream data(line.substr(4));
			data >> temp.ambientColour.x >> temp.ambientColour.y >> temp.ambientColour.z;
		}
		//Test for diffuse colour "Kd "
		else if (line.substr(0, 4) == "\tKd ") {
			std::stringstream data(line.substr(4));
			data >> temp.diffuseColour.x >> temp.diffuseColour.y >> temp.diffuseColour.z;
		}
		//Test for specular colour "Ks "
		else if (line.substr(0, 4) == "\tKs ") {
			std::stringstream data(line.substr(4));
			data >> temp.specularColour.x >> temp.specularColour.y >> temp.specularColour.z;
		}
		//Test for specular exponent (shininess) "Ns "
		else if (line.substr(0, 4) == "\tNs ") {
			std::stringstream data(line.substr(4));
			data >> temp.shininess;
		}
		//Test for dissolve "d "
		else if (line.substr(0, 3) == "\td ") {
			std::stringstream data(line.substr(3));
			data >> temp.transparency;
		}
	}
	if (temp.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(name, temp);
	}
}

GLuint MaterialLoader::LoadTexture(std::string name) {
	GLuint texture = TextureHandler::GetInstance()->GetTextureID(name);
	if (texture == 0) {
		TextureHandler::GetInstance()->CreateTexture(name, "./Resources/Textures/" + name + ".png");
		texture = TextureHandler::GetInstance()->GetTextureID(name);
	}
	return texture;
}