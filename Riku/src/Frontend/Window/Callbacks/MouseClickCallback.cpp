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
        //scene->clickPos
		auto clickPos = front::getMapClickPosition(window, (float) x, (float) y, scene->movingCameraTransform,
		                                             scene->config.fov, scene->aspect, 0.5f);
        int px = int(std::round(clickPos.x));
        int py = int(std::round(clickPos.y));
        auto units = scene->state.getUnits();
        scene->path.cost=0;
        scene->path.path.clear();
        if(scene->focusedUnitIndex>-1) {
            auto& unit = units[scene->focusedUnitIndex];
            scene->path = scene->state.getShortestPath(unit->getMapX(),unit->getMapY(),px,py);
        }
        else {
            scene->clickPos = {-1, -1};
            scene->focusedUnitIndex = -1;
            for (int i = 0; i < (int) units.size(); i++) {
                if (!units[i])
                    continue;
                if (units[i]->getMapX() == px && units[i]->getMapY() == py) {
                    scene->focusedUnitIndex = i;
                    break;
                }
            }
            if (scene->focusedUnitIndex == -1)
                scene->clickPos = {px, py};
        }
	}
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        scene->clickPos={-1,-1};
        scene->focusedUnitIndex=-1;
    }
}