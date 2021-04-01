#include "MaterialHandler.h"

std::unique_ptr<MaterialHandler> MaterialHandler::instance = nullptr;
std::unordered_map<std::string, Material> MaterialHandler::materialList = std::unordered_map<std::string, Material>();

MaterialHandler::MaterialHandler() {}

MaterialHandler::~MaterialHandler() {
	OnDestroy();
}

MaterialHandler* MaterialHandler::GetInstance() {
	if (instance.get() == nullptr) {
		instance.reset(new MaterialHandler);
	}
	return instance.get();
}

void MaterialHandler::OnDestroy() {
	if (materialList.size() > 0) {
		materialList.clear();
	}
}

void MaterialHandler::AddMaterial(std::string _name, Material _material) {
	materialList.insert(std::pair<std::string, Material>(_name, _material));
}

Material MaterialHandler::GetMaterial(std::string _name) const
{
	if (materialList.find(_name) != materialList.end()) {
		return materialList[_name];
	}
	return Material();
}