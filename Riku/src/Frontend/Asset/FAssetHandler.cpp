//
// Created by kamil-hp on 27.11.2021.
//

#include "FAssetHandler.h"
#include "../FrontendState.h"
#include "../JsonUtil.h"

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

bool front::AssetHandler::tryDraw(const std::string &key, const Shader &shader, Transform transform) const {
	if(assets.find(key)==assets.end())
		return false;
	const auto& a = assets.at(key);
	a.draw(shader, transform);
	return true;

}

const std::map<std::string, front::Asset>& front::AssetHandler::getMap() const {
    return assets;
}
