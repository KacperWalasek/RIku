//
// Created by kamil-hp on 27.11.2021.
//

#include "FAssetHandler.h"
#include "../FrontendState.h"
#include <fstream>
#ifdef __linux__
#include <jsoncpp/json/json.h>
#elif defined _WIN32
#include <json/json.h>
#endif // __linux__

namespace front {
	extern FrontendState state;
}

void front::AssetHandler::loadFiles() {
	const auto& handler = state.getAssetHandler();
	for(const auto& node: handler.assetNodes) {
		Json::Value root;
		std::string path = node.second.getPath()+"/";
		std::ifstream file(path+"front.json");
		if(!file.good())
		{
			std::cout << "Frontend file for " << path << "front.json not found\n";
			continue;
		}
		std::cout << "Frontend file for " << path << "front.json found\n";
		path = path.substr(3);
		Json::CharReaderBuilder builder;
		JSONCPP_STRING errs;
		if (!parseFromStream(builder, file, &root, &errs)) {
			std::cerr << errs << '\n';
			continue;
		}
		for(auto const& id: root.getMemberNames()) {
			Asset asset(id, path, root[id]);
			if(!asset.assetModels.empty()) {
				assets.insert(std::make_pair(id,std::move(asset)));
			}
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
