//
// Created by kamil-xkom on 07.12.2021.
//

#include "AssetTexture.h"
#include "../Model.h"
#include <filesystem>

std::map<std::string, Texture> front::AssetTexture::texs = {};
std::unique_ptr<Model> front::AssetTexture::model = nullptr;
front::Object front::AssetTexture::object;

void createMesh(std::unique_ptr<Model>& model, front::Object& object) {
    model = std::make_unique<Model>();
    Vertex v[4];
    v[0].Position = {-0.5,0.0,-0.5};
    v[1].Position = {-0.5,0.0,0.5};
    v[2].Position = {0.5,0.0,-0.5};
    v[3].Position = {0.5,0.0,0.5};
    v[0].TexCoords = {0.0,0.0};
    v[1].TexCoords = {0.0,1.0};
    v[2].TexCoords = {1.0,0.0};
    v[3].TexCoords = {1.0,1.0};

    std::vector<Vertex> vertices(v,v+4);
    std::vector indices = {0u,1u,2u,1u,2u,3u};
    std::vector<Texture> textures;
    model->meshes.emplace_back(vertices, indices, textures);
    object.SetModel(*model);
}

front::AssetTexture::AssetTexture(std::string &path, front::Transform transform, bool isCameraAdaptive): transform(transform), isCameraAdaptive(isCameraAdaptive) {
    if(model==nullptr) {
        createMesh(model,object);
    }
    auto p = std::filesystem::path(path);
    std::string absolute = "../"+p.string();
    std::string parent = "../"+p.parent_path().string();
    std::string filename = p.filename();
    auto tmpTexture = Texture("texture_diffuse",  p.filename(),p.parent_path());
    if(texs.find(absolute)==texs.end()) {
        texs[filename] = tmpTexture;
    }
    texture = &texs[filename];
}

void front::AssetTexture::draw(const Shader &shader, front::Transform t) const {
    if(!model)
        return;
    if(model->meshes[0].textures.empty())
        model->meshes[0].textures.push_back(*texture);
    else
        model->meshes[0].textures[0]=*texture;
    //set position (for not adaptive)
    if(isCameraAdaptive) {
        //todo
    }
    else {
        object.SetParent(t);
    }
    object.transform = transform;
    object.Draw(shader);
}
