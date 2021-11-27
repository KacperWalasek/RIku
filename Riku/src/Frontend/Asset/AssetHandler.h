//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_ASSETHANDLER_H
#define RIKU_ASSETHANDLER_H
#include "Asset.h"

namespace logic {
	class AssetHandler;
}

namespace front {
	class AssetHandler {
		std::map<std::string, Asset> assets;
	public:
		void loadFiles();
		const Asset& getAsset(const std::string& key) const;
		bool tryDraw(const std::string& key, const Shader &shader, Transform transform) const;
	};
}


#endif //RIKU_ASSETHANDLER_H
