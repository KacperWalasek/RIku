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


front::Asset::Asset(std::string name, const std::string& path, const Json::Value& value): name(std::move(name)) {
	//getting asset path
	if(!value.isArray())
		return;
	for(const auto& val: value) {
		std::string modelPath = val.get("path","").asString();
        std::string iconPath = val.get("icon","").asString();
		if(modelPath.empty() == iconPath.empty())
			continue;
		glm::vec3 pos={0.0f,0.0f,0.0f};
		if(val.isMember("pos")) {
			float x = val["pos"].get("x",0.0f).asFloat();
			float y = val["pos"].get("y",0.0f).asFloat();
			float z = val["pos"].get("z",0.0f).asFloat();
			pos = {x,y,z};
		}
		glm::vec3 rot={0.0f,0.0f,0.0f};
		if(val.isMember("rot")) {
			float x = val["rot"].get("x",0.0f).asFloat();
			float y = val["rot"].get("y",0.0f).asFloat();
			float z = val["rot"].get("z",0.0f).asFloat();
			rot = {x,y,z};
		}
		glm::vec3 scale={1.0f,1.0f,1.0f};
		if(val.isMember("scale")) {
			float x = val["scale"].get("x",1.0f).asFloat();
			float y = val["scale"].get("y",1.0f).asFloat();
			float z = val["scale"].get("z",1.0f).asFloat();
			scale = {x,y,z};
		}
        //tex scale effective only for models.
		float texScaleX=1.0f, texScaleY=1.0f;
		if(val.isMember("tex")) {
			texScaleX = val["tex"].get("x",1.0f).asFloat();
			texScaleY = val["tex"].get("y",1.0f).asFloat();
		}
        //Parameter effective only for icons. Overrides icon rotation
        bool cameraAdaptive = val["scale"].get("camera_adaptive",false).asBool();
        if(!modelPath.empty()) {
            modelPath = path + modelPath;
		    assetModels.emplace_back(modelPath, Transform(pos,rot,scale), texScaleX, texScaleY);
        }
        if(!iconPath.empty()) {
            iconPath = path + iconPath;
            assetTextures.emplace_back(iconPath,Transform(pos,rot,scale),cameraAdaptive);
        }
	}
}

void front::Asset::draw(const Shader &shader, Transform transform, glm::vec4 color) const {
	for(const auto& a: assetModels) {
        a.addToDrawManager(shader, transform,color);
        //a.draw(shader, transform);
	}
    for(const auto& a: assetTextures) {
        a.draw(shader, transform);
    }
    glActiveTexture(GL_TEXTURE0);
}
