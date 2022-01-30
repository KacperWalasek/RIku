// Kamil Boryczka
#pragma once
#include <map>
#include "Asset.h"

namespace logic {
	class AssetHandler {
	private:
		std::map<std::string, std::vector<Asset*> > childrenNodes;
		void traverse(Asset* assetPtr);
		void passFile(const std::string& path, const std::string& fileName, std::shared_ptr<IAssetInitializer> initializer);
		//root name
		std::string hash;
	public:
		std::map<std::string, Asset> assetNodes;
		void resolve();
		void findFiles(const std::string& path, std::shared_ptr<IAssetInitializer> initializer);
		const std::string& getHash() const { return hash; }
		std::optional<std::reference_wrapper<Asset>> findAsset(std::string name);
	};
}