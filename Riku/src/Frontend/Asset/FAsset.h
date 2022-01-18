//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_ASSETS_H
#define RIKU_ASSETS_H

#include <vector>
#include <map>
#include <string>
#include "AssetModel.h"
#include "AssetTexture.h"

namespace Json {
	class Value;
}
struct Shader;

namespace front {
	class Frustum;
	class Asset: IDrawable {
	private:
		std::string name;
		float frustumRadius; //radius of sphere for frustum culling. Includes Default value=0.5
		glm::vec3 frustumCenter; //centre of sphere for frustum culling. Includes Default value=0.5
		std::vector<AssetModel> assetModels;
        std::vector<AssetTexture> assetTextures;

		friend class AssetHandler;
    public:
		[[nodiscard]] const std::string& getName() const {return name;}
		Asset(std::string name, const std::string& path, const Json::Value& value);
		void draw(const Shader& shader, Transform transform) const override;
	};
}


#endif //RIKU_ASSETS_H
