//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_ASSETMODEL_H
#define RIKU_ASSETMODEL_H
#include <string>
#include <map>
#include "../IDrawable.h"
#include "../Texture.h"
#include <optional>

namespace front {
	class AssetModel: IDrawable {
	private:
		static std::map<std::string, Model> models;
	public:
		Model* model;
		std::optional<Texture> specular, diffuse, normal;
		Transform transform;
		AssetModel()=default;
		AssetModel(std::string& path, Transform transform, float texScaleX=1.0f, float texScaleY=1.0f);
        void draw(const Shader& shader, Transform transform) const override;
	};
}


#endif //RIKU_ASSETMODEL_H
