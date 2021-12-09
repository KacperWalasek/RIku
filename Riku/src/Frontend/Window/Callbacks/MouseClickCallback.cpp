//
// Created by kamil-hp on 01.12.2021.
//
#include "MouseClickCallback.h"
#include "../Scene.h"
#include "CEGUI/CEGUI.h"
#include "../../Util.h"

int findUnit(const std::vector<std::shared_ptr<const Unit> >& units, int px, int py) {
    //-1 if not found
    for (int i = 0; i < (int) units.size(); i++) {
        if (!units[i])
            continue;
        if (units[i]->getMapX() == px && units[i]->getMapY() == py) {
            return i;
        }
    }
    return -1;
}

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
        if(!scene->path.path.empty()) {
            auto& unit = units[scene->focusedUnitIndex];
            auto&& [toX, toY] = scene->path.path[scene->path.path.size()-1];
            if(unit && unit->getMapX()==px && unit->getMapY()==py) {
                scene->path.cost=0;
                scene->path.path.clear();
            }
            else if(toX==px && toY==py) {
                //make move
                scene->state.moveUnit(unit->getMapX(),unit->getMapY(),toX, toY);
                scene->path.cost=0;
                scene->path.path.clear();
            }
            else {
                //change unit
                int clickedUnit = findUnit(units, px, py);
                if(clickedUnit!=-1) {
                    scene->focusedUnitIndex = clickedUnit;
                    scene->path.cost=0;
                    scene->path.path.clear();
                }
            }
        }
        scene->path.cost=0;
        scene->path.path.clear();
        if(scene->focusedUnitIndex>-1) {
            auto& unit = units[scene->focusedUnitIndex];
            scene->path = scene->state.getShortestPath(unit->getMapX(),unit->getMapY(),px,py);
        }
        else {
            scene->clickPos = {-1, -1};
            scene->focusedUnitIndex = findUnit(units, px, py);
            if (scene->focusedUnitIndex == -1)
                scene->clickPos = {px, py};
        }
	}
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        if(!scene->path.path.empty()) {
            scene->path.cost = 0;
            scene->path.path.clear();
        }
        else {
            scene->clickPos = {-1, -1};
            scene->focusedUnitIndex = -1;
        }
    }
}