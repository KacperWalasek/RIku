#pragma once
#define _USE_MATH_DEFINES 
#include <GLFW/glfw3.h>
#include "../../Object.h"
#include "../../Config.h"

namespace front {
	class ScrollCallback
	{
		Transform& movingCameraTransform;
		Config& config;
	public:
		ScrollCallback(Transform& movingCameraTransform, Config& config) : movingCameraTransform(movingCameraTransform), config(config) {}
		
		void operator()(GLFWwindow* window, double xoffset, double yoffset) {
			if ((movingCameraTransform.position.y > config.minZoomHeight || yoffset < 0.0f) && (movingCameraTransform.position.y < config.maxZoomHeight || yoffset>0.0f))
				movingCameraTransform.position -= glm::rotateX(glm::vec3(0.f, yoffset * .5f, 0.f), (float)M_PI_4 - movingCameraTransform.rotation.x * .25f);
			else
				movingCameraTransform.position.y = std::min(40.0f, std::max(3.0f, movingCameraTransform.position.y));
		}
	};
}
