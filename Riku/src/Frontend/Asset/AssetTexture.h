//
// Created by kamil-xkom on 07.12.2021.
//

#ifndef RIKU_ASSETTEXTURE_H
#define RIKU_ASSETTEXTURE_H

#include <map>
#include "../Texture.h"
#include "../IDrawable.h"

namespace front {
    class AssetTexture: IDrawable {
    private:
        static std::map<std::string, Texture> texs;
    public:
        Texture *texture;
        Transform transform;
        bool isCameraAdaptive;
        AssetTexture(std::string &path, Transform transform, bool isCameraAdaptive);
        void draw(const Shader& shader, Transform transform) const override;

    };
}


#endif //RIKU_ASSETTEXTURE_H
