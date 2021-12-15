//
// Created by kamil-xkom on 07.12.2021.
//

#ifndef RIKU_ASSETTEXTURE_H
#define RIKU_ASSETTEXTURE_H

#include <map>
#include <memory>
#include "../Texture.h"
#include "../IDrawable.h"
#include "../Mesh.h"

namespace front {
    class AssetTexture: IDrawable {
    private:
        static std::map<std::string, Texture> texs;
        static std::unique_ptr<Model> model;
        static Object object;
        Texture *texture;
    public:
        Transform transform;
        bool isCameraAdaptive;
        AssetTexture(std::string &path, Transform transform, bool isCameraAdaptive);
        void draw(const Shader& shader, Transform t, glm::vec4 color) const override;
        void draw(const Shader& shader, Transform t) const override {draw(shader, t, {1.0,1.0,1.0,1.0});};

    };
}


#endif //RIKU_ASSETTEXTURE_H
