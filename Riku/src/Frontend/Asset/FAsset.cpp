//
// Created by kamil-hp on 27.11.2021.
//

#include "FAsset.h"
#include <iostream>
#include <utility>
#ifdef __linux__
#include <jsoncpp/json/json.h>
#elif defined _WIN32
#include <json/json.h>
#endif // __linux__
#include "../Model.h"
#include <filesystem>

std::tuple<std::optional<Texture>,std::optional<Texture>,std::optional<Texture>> checkTextures(const Json::Value& val, const std::string& path){
	std::optional<Texture> diffuse, specular, normal;
	if(val.isMember("diffuse") && val["diffuse"].isString()) {
		std::string path2 = path + val["diffuse"].asString();
		auto p = std::filesystem::path(path2);
		std::string filename = p.filename().string();
		diffuse = Texture("texture_diffuse",val["diffuse"].asString(), p.parent_path().string());
	}
	if(val.isMember("specular") && val["specular"].isString()) {
		std::string path2 = path + val["specular"].asString();
		auto p = std::filesystem::path(path2);
		std::string filename = p.filename().string();
		specular=Texture("texture_specular",filename, p.parent_path().string());
	}
	if(val.isMember("normal") && val["normal"].isString()) {
		std::string path2 = path + val["normal"].asString();
		auto p = std::filesystem::path(path2);
		std::string filename = p.filename().string();
		normal=Texture("texture_normal",filename, p.parent_path().string());
	}
	return {diffuse, specular, normal};
}


front::Asset::Asset(std::string name, const std::string& path, const Json::Value& value): name(std::move(name)) {
	frustumRadius=0.5f;
	frustumCenter={0.0f,0.0f,0.0f};
	//getting asset path
	if(!value.isArray())
		return;
	for(const auto& val: value) {
		std::string modelPath = val.get("path", "").asString();
		std::string iconPath = val.get("icon", "").asString();
		/*if (modelPath.empty() != iconPath.empty())*/ {
			//check if is frustum info. Should be unique
			if (val.isMember("frustum")) {
				frustumRadius = val.get("frustum_radius", 0.5f).asFloat();
				if (val.isMember("frustum_center")) {
					float x = val["frustum_center"].get("x", 0.0f).asFloat();
					float y = val["frustum_center"].get("y", 0.0f).asFloat();
					float z = val["frustum_center"].get("z", 0.0f).asFloat();
					frustumCenter = {x, y, z};
				}
				continue;
			}
			//check for ground asset
			if (val.isMember("ground")) {
				auto&&[specular, diffuse, normal]=checkTextures(val, path);
				assetModels.emplace_back();
				assetModels.back().diffuse = diffuse;
				assetModels.back().normal = normal;
				assetModels.back().specular = specular;
			}
			glm::vec3 pos = {0.0f, 0.0f, 0.0f};
			if (val.isMember("pos")) {
				float x = val["pos"].get("x", 0.0f).asFloat();
				float y = val["pos"].get("y", 0.0f).asFloat();
				float z = val["pos"].get("z", 0.0f).asFloat();
				pos = {x, y, z};
			}
			glm::vec3 rot = {0.0f, 0.0f, 0.0f};
			if (val.isMember("rot")) {
				float x = val["rot"].get("x", 0.0f).asFloat();
				float y = val["rot"].get("y", 0.0f).asFloat();
				float z = val["rot"].get("z", 0.0f).asFloat();
				rot = {x, y, z};
			}
			glm::vec3 scale = {1.0f, 1.0f, 1.0f};
			if (val.isMember("scale")) {
				float x = val["scale"].get("x", 1.0f).asFloat();
				float y = val["scale"].get("y", 1.0f).asFloat();
				float z = val["scale"].get("z", 1.0f).asFloat();
				scale = {x, y, z};
			}
			//tex scale effective only for models.
			float texScaleX = 1.0f, texScaleY = 1.0f;
			if (val.isMember("tex")) {
				texScaleX = val["tex"].get("x", 1.0f).asFloat();
				texScaleY = val["tex"].get("y", 1.0f).asFloat();
			}
			//textures
			auto&&[specular, diffuse, normal]=checkTextures(val, path);
			//Parameter effective only for icons. Overrides icon rotation
			bool cameraAdaptive = val["scale"].get("camera_adaptive", false).asBool();
			if (!modelPath.empty()) {
				modelPath = path + modelPath;
				assetModels.emplace_back(modelPath, Transform(pos, rot, scale), texScaleX, texScaleY);
				assetModels.back().diffuse = diffuse;
				assetModels.back().normal = normal;
				assetModels.back().specular = specular;
			}
			if (!iconPath.empty()) {
				iconPath = path + iconPath;
				assetTextures.emplace_back(iconPath, Transform(pos, rot, scale), cameraAdaptive);
			}
		}
	}
}

void front::Asset::draw(const Shader &shader, Transform transform) const {
	for(const auto& a: assetModels) {
        a.draw(shader, transform);
	}
    for(const auto& a: assetTextures) {
        a.draw(shader, transform);
    }
}
