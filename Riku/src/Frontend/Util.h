//
// Created by kamil-hp on 29.11.2021.
//

#ifndef RIKU_UTIL_H
#define RIKU_UTIL_H

#include <GLFW/glfw3.h>
#include "Object.h"

namespace front {
	glm::vec3 getRay(GLFWwindow* window, const glm::mat4& projection, const glm::mat4& view, float mouseX, float mouseY) {
		//based on https://github.com/capnramses/antons_opengl_tutorials_book/blob/master/07_ray_picking/main.cpp by Anton Gerdelan
		//license in https://github.com/capnramses/antons_opengl_tutorials_book/blob/master/LICENCE.md (CC BY 3.0)
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glm::vec4 rayClip = {mouseX/(float)width*2.0f-1.0f, 1.0f-mouseY/(float)height*2.0f, -1.0f, 1.0f};
		glm::vec4 rayEye = inverse(projection) * rayClip;
		rayEye = glm::vec4(rayEye.x,rayEye.y,-1.0f,0.0f);
		glm::vec3 rayWor = glm::normalize(glm::vec3(inverse(view) * rayEye));
		return rayWor;
	}

	glm::vec2 getMapClickPosition(GLFWwindow* window, float mouseX, float mouseY, const front::Transform& camera, float fov, float aspect, float level) {
		//matrices
		glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
		glm::mat4 view = camera.calculateViewMatrix();
		//main calculations
		auto ray = getRay(window, projection, view, mouseX, mouseY);
		return glm::vec2(camera.position.x-(camera.position.y-level)*ray.x/ray.y,camera.position.z-(camera.position.y-level)*ray.z/ray.y);

	}
}
#endif //RIKU_UTIL_H
