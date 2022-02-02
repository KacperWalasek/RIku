//
// Created by kamil-hp on 11.01.2022.
//
#include "Util.h"
#include "Window/Scene.h"
#include <filesystem>

glm::vec3 front::getRelativeRay(const glm::mat4& projection, const glm::mat4& view, float x, float y) {
	//based on https://github.com/capnramses/antons_opengl_tutorials_book/blob/master/07_ray_picking/main.cpp by Anton Gerdelan
	//license in https://github.com/capnramses/antons_opengl_tutorials_book/blob/master/LICENCE.md (CC BY 3.0)
	//vector is normalized
	glm::vec4 rayClip = {x*2.0f-1.0f, y*2.0f-1.0f, -1.0f, 1.0f};
	glm::vec4 rayEye = inverse(projection) * rayClip;
	rayEye = glm::vec4(rayEye.x,rayEye.y,-1.0f,0.0f);
	glm::vec3 rayWor = glm::normalize(glm::vec3(inverse(view) * rayEye));
	return rayWor;
}

glm::vec3 front::getRay(GLFWwindow* window, const glm::mat4& projection, const glm::mat4& view, float mouseX, float mouseY) {
	//based on https://github.com/capnramses/antons_opengl_tutorials_book/blob/master/07_ray_picking/main.cpp by Anton Gerdelan
	//license in https://github.com/capnramses/antons_opengl_tutorials_book/blob/master/LICENCE.md (CC BY 3.0)
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return getRelativeRay(projection, view, mouseX/(float)width, 1.0f-mouseY/(float)height);
}

glm::vec2 front::getMapClickPosition(GLFWwindow* window, const Scene& scene, float mouseX, float mouseY, float level) {
	//main calculations
	auto& camera = scene.getCamera();
	auto ray = getRay(window, scene.getProjection(), scene.getView(), mouseX, mouseY);
	return {camera.position.x-(camera.position.y-level)*ray.x/ray.y,camera.position.z-(camera.position.y-level)*ray.z/ray.y};
}

std::vector<std::string> front::getSaveFiles() {
	constexpr std::string_view path = "../saves/";
	std::vector<std::string> files;
	for(const auto& entry: std::filesystem::directory_iterator(path)) {
		if(entry.is_regular_file() && entry.path().extension().string()==".sav") {
			files.push_back(entry.path().string());
		}
	}
	return files;
}
