//
// Created by kamil-xkom on 07.12.2021.
//

#ifndef RIKU_IDRAWABLE_H
#define RIKU_IDRAWABLE_H

#include "Object.h"

namespace front {
    class IDrawable {
        virtual void draw(const Shader& shader, Transform transform, glm::vec4 color) const=0;
        virtual void draw(const Shader& shader, Transform transform) const=0;
    };
}

#endif //RIKU_IDRAWABLE_H
