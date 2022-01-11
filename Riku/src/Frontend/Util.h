//
// Created by kamil-hp on 29.11.2021.
//

#ifndef RIKU_UTIL_H
#define RIKU_UTIL_H

#include "Transform.h"

struct GLFWwindow;
namespace front {
	class Scene;
	glm::vec3 getRelativeRay(const glm::mat4& projection, const glm::mat4& view, float x, float y);
	glm::vec3 getRay(GLFWwindow* window, const glm::mat4& projection, const glm::mat4& view, float mouseX, float mouseY);
	glm::vec2 getMapClickPosition(GLFWwindow* window, const Scene& scene, float mouseX, float mouseY, float level);
}
#endif //RIKU_UTIL_H
