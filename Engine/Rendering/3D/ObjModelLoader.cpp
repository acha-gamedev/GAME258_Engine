#include "ObjModelLoader.h"
#include "../../Core/Debug.h"

ObjModelLoader::ObjModelLoader() : material(), boundBox() {}

ObjModelLoader::~ObjModelLoader() {
	vertices.clear();
	vertices.shrink_to_fit();
	normals.clear();
	normals.shrink_to_fit();
	uvCoords.clear();
	uvCoords.shrink_to_fit();
	indices.clear();
	indices.shrink_to_fit();
	normalIndices.clear();
	normalIndices.shrink_to_fit();
	uvIndices.clear();
	uvIndices.shrink_to_fit();
	vertexObjects.clear();
	vertexObjects.shrink_to_fit();
	submeshes.clear();
	submeshes.shrink_to_fit();
}

void ObjModelLoader::LoadOBJ(std::string _objFilepath, std::string _matFilepath) {
	LoadMaterialLibrary(_matFilepath);
	LoadModel(_objFilepath);
}

std::vector<SubMesh> ObjModelLoader::GetSubMeshes() {
	return submeshes;
}

void ObjModelLoader::LoadModel(std::string _objFilepath) {
	std::ifstream file(_objFilepath.c_str(), std::ios::in);
	if (!file) {
		Debug::LogError("Could not open OBJ file " + _objFilepath, "Engine/Rendering/3D/ObjModelLoader", __LINE__);
		return;
	}

	std::string line;
	boundBox.maxVertex = glm::vec3(-1000.0f);
	boundBox.minVertex = glm::vec3(1000.0f);
	while (std::getline(file, line)) {
		//Test for position data "v "
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			if (x > boundBox.maxVertex.x) {
				boundBox.maxVertex.x = x;
			}
			else if (x < boundBox.minVertex.x) {
				boundBox.minVertex.x = x;
			}

			if (y > boundBox.maxVertex.y) {
				boundBox.maxVertex.y = y;
			}
			else if (y < boundBox.minVertex.y) {
				boundBox.minVertex.y = y;
			}

			if (z > boundBox.maxVertex.z) {
				boundBox.maxVertex.z = z;
			}
			else if (z < boundBox.minVertex.z) {
				boundBox.minVertex.z = z;
			}
			vertices.push_back(glm::vec3(x, y, z));
		}
		//Test for normal data "vn "
		else if (line.substr(0, 3) == "vn ") {
			std::stringstream v(line.substr(3));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		//Test for texture data "vt "
		else if (line.substr(0, 3) == "vt ") {
			std::stringstream v(line.substr(3));
			float x, y, z;
			v >> x >> y >> z;
			uvCoords.push_back(glm::vec2(x, y));
		}
		//Test for face data "f "
		// point order is f v/t/n v/t/n v/t/n
		else if (line.substr(0, 2) == "f ") {
			//std::string raw = line.substr(2);
			//while (raw.find("/") != std::string::npos) {
			//	raw.replace(raw.find("/"), 1, " ");
			//}
			//std::stringstream format(raw);
			unsigned int v1, t1, n1, v2, t2, n2, v3, t3, n3;
			//format >> v1 >> t1 >> n1 >> v2 >> t2 >> n2 >> v3 >> t3 >> n3;
			std::stringstream format(line.substr(2));
			char slash;
			format >> v1 >> slash >> t1 >> slash >> n1 >>
				v2 >> slash >> t2 >> slash >> n2 >>
				v3 >> slash >> t3 >> slash >> n3;
			indices.push_back(v1 - 1);
			indices.push_back(v2 - 1);
			indices.push_back(v3 - 1);
			normalIndices.push_back(n1 - 1);
			normalIndices.push_back(n2 - 1);
			normalIndices.push_back(n3 - 1);
			uvIndices.push_back(t1 - 1);
			uvIndices.push_back(t2 - 1);
			uvIndices.push_back(t3 - 1);
		}
		//Test for MTL data "usemtl "
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcess();
			}
			LoadMaterial(line.substr(7));
		}
	}
	if (indices.size() > 0) {
		PostProcess();
	}
}

void ObjModelLoader::LoadMaterialLibrary(std::string _matFilepath) {
	MaterialLoader::LoadMaterial(_matFilepath);
	//std::ifstream file(_matFilepath.c_str(), std::ios::in);
	//if (!file) {
	//	Debug::LogError("Could not open MTL file " + _matFilepath, "Engine/Rendering/3D/ObjModelLoader", __LINE__);
	//	return;
	//}

	//std::string line;
	//while (std::getline(file, line)) {
	//	if (line.substr(0, 7) == "newmtl ") {
	//		LoadMaterial(line.substr(7));
	//	}
	//}
}

void ObjModelLoader::LoadMaterial(std::string _name) {
	material = MaterialHandler::GetInstance()->GetMaterial(_name);
	//if (material.diffuseMap == 0) {
	//	TextureHandler::GetInstance()->CreateTexture(_name, "Resources/Textures/" + _name + ".png");
	//	textureID = TextureHandler::GetInstance()->GetTextureID(_texName);
	//}
	//
}

void ObjModelLoader::PostProcess() {
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.uvCoords = uvCoords[uvIndices[i]];
		vertexObjects.push_back(vert);
	}
	SubMesh temp;
	temp.vertices = vertexObjects;
	temp.material = material;
	temp.indexList = indices;
	submeshes.push_back(temp);

	indices.clear();
	normalIndices.clear();
	uvIndices.clear();
	vertexObjects.clear();
	material = Material();
}