//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_FASSETHANDLER_H
#define RIKU_FASSETHANDLER_H
#include "FAsset.h"
#include "../../GameLogic/Assets/AssetHandler.h"

namespace front {
	struct Frustum;
	struct Transform;
	class AssetHandler {
		std::map<std::string, Asset> assets;
		const logic::AssetHandler& handler;
        void loadFile(const std::string& path);
	public:
		explicit AssetHandler(const logic::AssetHandler& assetHandler);
		void loadFiles();
		const Asset& getAsset(const std::string& parentPath) const;
		bool tryDraw(const std::string& key, const Shader &shader, const Transform& transform, const Frustum& frustum) const;
        const std::map<std::string, Asset>& getMap() const;
		bool drawGround(const std::string& key, const std::string& modelKey, const Shader &shader, Transform transform) const;
	};
}


#endif //RIKU_FASSETHANDLER_H
