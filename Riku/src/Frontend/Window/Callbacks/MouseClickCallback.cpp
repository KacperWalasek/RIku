//
// Created by kamil-hp on 01.12.2021.
//
#include "MouseClickCallback.h"
#include "../Scene.h"
#include "CEGUI/CEGUI.h"
#include "../../Util.h"

void front::MouseClickCallback::operator()(GLFWwindow* window, int button, int action, int mods) {
	if (activeGUI->on_mouse_click(button, action)) return;
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		scene->clickPos = front::getMapClickPosition(window, (float) x, (float) y, scene->movingCameraTransform,
		                                             scene->config.fov, scene->aspect, 0.5f);
	}
}