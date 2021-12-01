//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_FASSETHANDLER_H
#define RIKU_FASSETHANDLER_H
#include "FAsset.h"
#include "../../GameLogic/Assets/AssetHandler.h"

namespace front {
	class AssetHandler {
		std::map<std::string, Asset> assets;
		const logic::AssetHandler& handler;
	public:
		AssetHandler(const logic::AssetHandler& assetHandler);
		void loadFiles();
		const Asset& getAsset(const std::string& key) const;
		bool tryDraw(const std::string& key, const Shader &shader, Transform transform) const;
	};
}


#endif //RIKU_FASSETHANDLER_H
