//
// Created by kamil-xkom on 08.12.2021.
//

#ifndef RIKU_TRANSFORM_H
#define RIKU_TRANSFORM_H
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace front {

    glm::vec3 rotate(const glm::vec3 &pos, const glm::vec3 &rot);

    struct Transform {
        glm::vec3 position, rotation, scale;

        explicit Transform(const glm::vec3 &pos = glm::vec3(0.0f), const glm::vec3 &rot = glm::vec3(0.0f),
                           const glm::vec3 &sc = glm::vec3(1.0f));

        static const Transform Default;

        [[nodiscard]] glm::vec3 CalculateRelativePosition(const glm::vec3 &pos) const;

        [[nodiscard]] glm::vec3 CalculateRelativeFront(const glm::vec3 &pos) const;

        [[nodiscard]] glm::mat4 CalculateMatrix(const Transform &relativeTo = Default) const;

        glm::mat4 calculateViewMatrix() const {
            auto front=rotate({0.0f,0.0f,1.0f},rotation);
            auto up=rotate({0.0f,1.0f,0.0f},rotation);
            return glm::lookAt(position, position + front, up);
        }
    };
}

#endif //RIKU_TRANSFORM_H
