#include "AssetHandler.h"
#include <filesystem>
#include <hash-library/sha256.h>

namespace logic{

	void AssetHandler::passFile(const std::string& path, const std::string& fileName, std::shared_ptr<IAssetInitializer> initializer) {
		Asset newAsset(path, fileName, initializer);
		std::string assetName = newAsset.name;
		std::string assetParent = newAsset.parent_name;
		assetNodes[newAsset.name] = std::move(newAsset);
		if (assetName != "root") {
			Asset* assetPtr = &assetNodes[assetName];
			if (assetNodes.find(assetParent) == assetNodes.end())
				childrenNodes[assetParent] = std::vector({ assetPtr });
			else 
				childrenNodes[assetParent].push_back(assetPtr);
		}
	}

	void AssetHandler::traverse(Asset* assetPtr) {
		if (assetPtr == nullptr)
			return;
		std::vector<Asset*> children = childrenNodes[assetPtr->getName()];
		for (Asset* child : children) {
			if (child == nullptr)
				continue;
			child->updateFromParent(*assetPtr);
			traverse(child);
		}
	}

	void AssetHandler::resolve() {
		traverse(&assetNodes["root"]);
		//calculating hash
		std::vector<std::string> hashdata;
		for (const auto& a : assetNodes) {
			hashdata.push_back(a.second.getHash());
		}
		std::sort(hashdata.begin(), hashdata.end());
		std::string hashed;
		for (const std::string& s : hashdata) {
			hashed += s;
		}
		SHA256 sha256;
		hash = sha256(hashed);
	}

	void AssetHandler::findFiles(const std::string& path, std::shared_ptr<IAssetInitializer> initializer) {
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_directory()) {
				//it is asset
				std::string path2 = entry.path().string() + "/script.lua";
				if (std::filesystem::exists(path2)) {
					std::cout << "Loading asset " << std::filesystem::relative(entry.path(), path) << "\n";
					passFile(entry.path().string(), "script.lua", initializer);
				}
				else
					std::cerr << entry.path() << " is not a valid asset\n";
			}
		}
		resolve();
	}

	std::optional<std::reference_wrapper<Asset>> AssetHandler::findAsset(std::string name)
	{
		auto it = assetNodes.find(name);
		if (it == assetNodes.end()) {
			std::cerr << name +" configuration file not found" << std::endl;
			return std::nullopt;
		}
		return it->second;
	}

}
