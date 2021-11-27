//
// Created by kamil-hp on 27.11.2021.
//

#include "../Model.h"
#include "AssetModel.h"
#include <filesystem>

std::map<std::string, Model> front::AssetModel::models = {};

front::AssetModel::AssetModel(std::string& path, Transform transform, float texScaleX, float texScaleY): transform(transform) {
	std::string absolute = std::filesystem::absolute(path);
	if(models.find(absolute)==models.end()) {
		models[absolute] = Model(path, texScaleX, texScaleY);
	}
	model = &models[absolute];
}
