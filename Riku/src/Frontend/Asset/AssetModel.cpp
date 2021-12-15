//
// Created by kamil-hp on 27.11.2021.
//

#include "../Model.h"
#include "AssetModel.h"
#include "../DrawManager/ObjectDrawManager.h"
#include "../Shader.h"
#include <filesystem>

std::map<std::string, Model> front::AssetModel::models = {};

front::AssetModel::AssetModel(std::string& path, Transform transform, float texScaleX, float texScaleY): transform(transform) {
	std::string absolute = std::filesystem::absolute(path).string();
	if(models.find(absolute)==models.end()) {
		models[absolute] = Model(path, texScaleX, texScaleY);
	}
	model = &models[absolute];
}

void front::AssetModel::draw(const Shader &shader, front::Transform t, glm::vec4 color) const {
    Object object(*model);
    object.transform=transform;
    object.SetParent(t);

    object.Draw(shader);
}

void front::AssetModel::addToDrawManager(const Shader &shader, front::Transform t, glm::vec4 color) const {
    Object object(*model);
    object.transform=transform;
    object.SetParent(t);
    ObjectDrawManager::add(object);
}
