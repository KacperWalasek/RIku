//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_ASSETMODEL_H
#define RIKU_ASSETMODEL_H
#include <string>
#include <map>
#include "../IDrawable.h"

namespace front {
	class AssetModel: IDrawable {
	private:
		static std::map<std::string, Model> models;
        Model* model;
	public:
		Transform transform;
		AssetModel(std::string& path, Transform transform, float texScaleX=1.0f, float texScaleY=1.0f);
        void draw(const Shader& shader, Transform transform) const override;
	};
}


#endif //RIKU_ASSETMODEL_H
