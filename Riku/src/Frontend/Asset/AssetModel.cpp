//
// Created by kamil-hp on 27.11.2021.
//

#include "../Model.h"
#include "AssetModel.h"
#include <filesystem>

std::map<std::string, Model> front::AssetModel::models = {};

front::AssetModel::AssetModel(std::string& path, Transform transform, float texScaleX, float texScaleY): transform(transform) {
	std::string absolute = std::filesystem::absolute(path).string();
	if(models.find(absolute)==models.end()) {
		models[absolute] = Model(path, texScaleX, texScaleY);
	}
	model = &models[absolute];
}

void front::AssetModel::draw(const Shader &shader, front::Transform t) const {
	if(model==nullptr)
		return;
    Object object(*model);
    object.transform=transform;
    object.SetParent(t);
	std::vector<Texture> backupTextures;
	if(specular || diffuse || normal ) {
		bool wasSpec=false, wasDiff=false, wasNorm=false;
		for (auto &tex: model->meshes[0].textures) {
			backupTextures.push_back(tex);
			if (!wasDiff && tex.type == "texture_diffuse" && diffuse) {
				tex=*diffuse;
				wasDiff=true;
			}
			if (!wasSpec && tex.type == "texture_specular" && specular) {
				tex=*specular;
				wasSpec=true;
			}
			if (!wasNorm && tex.type == "texture_normal" && normal) {
				tex=*normal;
				wasNorm=true;
			}
		}
		if(!wasDiff && diffuse)
			model->meshes[0].textures.push_back(*diffuse);
		if(!wasSpec && specular)
			model->meshes[0].textures.push_back(*specular);
		if(!wasNorm && normal)
			model->meshes[0].textures.push_back(*normal);
	}
    object.Draw(shader);
	if(specular || diffuse || normal )
		model->meshes[0].textures=std::move(backupTextures);
}
