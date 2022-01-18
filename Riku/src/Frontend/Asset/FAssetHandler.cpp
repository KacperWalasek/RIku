//
// Created by kamil-hp on 27.11.2021.
//

#include "FAssetHandler.h"
#include "../FrontendState.h"
#include "../JsonUtil.h"
#include "../FrustumCulling.h"

front::AssetHandler::AssetHandler(const logic::AssetHandler& assetHandler)
	: handler(assetHandler)
{
}

void front::AssetHandler::loadFiles() {
    std::cout << "Loading assets for frontend\n";
    loadFile("../assets/");
	for(const auto& node: handler.assetNodes) {
        const auto& path = node.second.getPath()+"/";
        loadFile(path);
	}
	std::cout << "Assets loaded successfully\n\n";
}

void front::AssetHandler::loadFile(const std::string& parentPath) {
    Json::Value root = getJsonFromFile(parentPath+"front.json",false);
    std::string path2 = parentPath.substr(3);
    for(auto const& id: root.getMemberNames()) {
        Asset asset(id, path2, root[id]);
        if(!asset.assetModels.empty() || !asset.assetTextures.empty()) {
            assets.insert(std::make_pair(id,std::move(asset)));
        }
    }
}

const front::Asset &front::AssetHandler::getAsset(const std::string& key) const {
	return assets.at(key);
}

bool front::AssetHandler::tryDraw(const std::string &key, const Shader &shader, const Transform& transform, const Frustum& frustum) const {
	if(assets.find(key)==assets.end())
		return false;
	const auto& a = assets.at(key);
	float r = a.frustumRadius * std::max({transform.scale.x,transform.scale.y,transform.scale.z});
	if(!frustum.isSphereOn(rotate(a.frustumCenter, transform.rotation), r, transform))
		return true;
	a.draw(shader, transform);
	return true;

}

const std::map<std::string, front::Asset>& front::AssetHandler::getMap() const {
    return assets;
}

bool front::AssetHandler::drawGround(const std::string &key, const std::string &modelKey, const Shader &shader,
                                     front::Transform transform) const {
	//assumes that asset with key modelKey has exactly one model
	if(assets.find(key)==assets.end() || assets.find(modelKey)==assets.end())
		return false;
	AssetModel tmpAsset;
	tmpAsset.model = assets.at(modelKey).assetModels[0].model;
	const AssetModel& ground = assets.at(key).assetModels[0];
	tmpAsset.diffuse=ground.diffuse;
	tmpAsset.specular=ground.specular;
	tmpAsset.normal=ground.normal;
	tmpAsset.draw(shader, transform);
	assets.at(modelKey).draw(shader,transform);
	return true;
}
