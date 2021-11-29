//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_ASSETMODEL_H
#define RIKU_ASSETMODEL_H
#include <string>
#include <map>
#include "../Object.h"

namespace front {
	class AssetModel {
	private:
		static std::map<std::string, Model> models;
	public:
		Model* model;
		Transform transform;
		AssetModel(std::string& path, Transform transform, float texScaleX=1.0f, float texScaleY=1.0f);
	};
}


#endif //RIKU_ASSETMODEL_H
