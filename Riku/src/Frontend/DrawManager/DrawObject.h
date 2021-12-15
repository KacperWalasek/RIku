//
// Created by kamil-xkom on 08.12.2021.
//

#ifndef RIKU_DRAWOBJECT_H
#define RIKU_DRAWOBJECT_H
#include "../Object.h"
#include "../Mesh.h"
#include <optional>

namespace front {
    struct DrawObject {
        const Mesh* mesh;
        Transform transform;
        std::optional<Transform> parent;
        glm::vec4 color;
        DrawObject(const Mesh& mesh, Transform transform, glm::vec4 color={1.0,1.0,1.0,1.0}, std::optional<Transform> parent=std::nullopt):
            mesh(&mesh), transform(transform), parent(parent), color(color) {}
    };
}

#endif //RIKU_DRAWOBJECT_H
