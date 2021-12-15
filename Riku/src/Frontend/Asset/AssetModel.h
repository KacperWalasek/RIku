//
// Created by kamil-hp on 27.11.2021.
//

#ifndef RIKU_ASSETMODEL_H
#define RIKU_ASSETMODEL_H
#include <string>
#include <map>
#include "../IDrawable.h"
struct Shader;
namespace front {
	class AssetModel: IDrawable {
	private:
		static std::map<std::string, Model> models;
        Model* model;
	public:
		Transform transform;
		AssetModel(std::string& path, Transform transform, float texScaleX=1.0f, float texScaleY=1.0f);
        void draw(const Shader& shader, Transform transform, glm::vec4 color) const override;
        void draw(const Shader& shader, Transform t) const override {draw(shader, t, {1.0,1.0,1.0,1.0});};
        void addToDrawManager(const Shader& shader, Transform transform, glm::vec4 color) const;
	};
}


#endif //RIKU_ASSETMODEL_H
