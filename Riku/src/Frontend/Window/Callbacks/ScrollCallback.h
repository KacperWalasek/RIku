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
		CEGUI::GUI* activeGUI;
	public:
		ScrollCallback(Transform& movingCameraTransform, Config& config, CEGUI::GUI* activeGUI) 
			: movingCameraTransform(movingCameraTransform), config(config), activeGUI(activeGUI) {}
		
		void operator()(GLFWwindow* window, double xoffset, double yoffset) {
			if (activeGUI->on_scroll(yoffset)) return;
			if ((movingCameraTransform.position.y > config.minZoomHeight || yoffset < 0.0f) && (movingCameraTransform.position.y < config.maxZoomHeight || yoffset>0.0f))
				movingCameraTransform.position -= rotate({0.f, yoffset * .5f, 0.f}, {movingCameraTransform.rotation.x-(float)M_PI_2,movingCameraTransform.rotation.y,.0f});
			else
				movingCameraTransform.position.y = std::min(config.maxZoomHeight, std::max(config.minZoomHeight, movingCameraTransform.position.y));
		}
	};
}

