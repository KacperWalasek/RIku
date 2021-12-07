//
// Created by kamil-xkom on 07.12.2021.
//

#include "AssetTexture.h"
#include <filesystem>

std::map<std::string, Texture> front::AssetTexture::texs = {};

front::AssetTexture::AssetTexture(std::string &path, front::Transform transform, bool isCameraAdaptive): transform(transform), isCameraAdaptive(isCameraAdaptive) {
    auto p = std::filesystem::path(path);
    std::string absolute = p.string();
    std::string parent = p.parent_path().string();
    std::string filename = p.filename();
    if(texs.find(absolute)==texs.end()) {
        texs[filename] = Texture("icon", p.parent_path(), p.filename());
    }
    texture = &texs[absolute];
}

void front::AssetTexture::draw(const Shader &shader, front::Transform transform) const {
    //TODO
}
