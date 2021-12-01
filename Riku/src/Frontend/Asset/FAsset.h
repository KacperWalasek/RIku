//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_ASSETS_H
#define RIKU_ASSETS_H

#include <vector>
#include <map>
#include <string>
#include "AssetModel.h"

namespace Json {
	class Value;
}
struct Shader;

namespace front {
	struct Transform;
	class Asset {
	private:
		std::map<std::string, Transform> asset;
		std::string name;
		std::vector<AssetModel> assetModels;
		friend class AssetHandler;
	public:
		[[nodiscard]] const std::string& getName() const {return name;}
		Asset(std::string name, const std::string& path, const Json::Value& value);
		void draw(const Shader& shader, Transform transform) const;
	};
}


#endif //RIKU_ASSETS_H
