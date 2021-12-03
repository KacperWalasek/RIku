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
	for(const auto& node: handler.assetNodes) {
		std::string path = node.second.getPath()+"/";
		Json::Value root = getJsonFromFile(path+"front.json",false);
		path = path.substr(3);
		for(auto const& id: root.getMemberNames()) {
			Asset asset(id, path, root[id]);
			if(!asset.assetModels.empty()) {
				assets.insert(std::make_pair(id,std::move(asset)));
			}
		}
	}
	std::cout << "Assets loaded successfully\n\n";
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
