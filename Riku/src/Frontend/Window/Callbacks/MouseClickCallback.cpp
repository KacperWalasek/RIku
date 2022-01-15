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
int findMiniUnit(const std::vector<std::shared_ptr<const minigame::MiniUnit> >& units, int px, int py) {
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
void front::MouseClickCallback::MiniGameLeftClick(int px, int py) {
	auto units = scene->state.getMiniUnits();
	if(!scene->path.path.empty()) {
		auto& unit = units[scene->focusedUnitIndex];
		auto to = scene->path.path[scene->path.path.size() - 1];
		auto&&[toX, toY] = to;
		if(unit && unit->getMapX()==px && unit->getMapY()==py) {
			scene->path.cost=0;
			scene->path.path.clear();
		}
		else if(toX==px && toY==py) {
			const minigame::MiniTile& targetTile = scene->state.getMiniMap()[toX][toY];
			bool isAttack=false;
			if(targetTile.unit && targetTile.unit->getOwner()!=units[scene->focusedUnitIndex]->getOwner()) {
				isAttack=true;
				if(scene->path.path.size()>1u) {
					scene->path.path.pop_back();
					scene->path = scene->state.getShortestPath(unit->getMapX(), unit->getMapY(),
					                                           scene->path.path.back().first,
					                                           scene->path.path.back().second);
					scene->state.moveUnit(unit->getMapX(), unit->getMapY(), scene->path.path.back().first,
					                      scene->path.path.back().second);
				}
				else {
					scene->path.path={{unit->getMapX(), unit->getMapY()}};
				}
			}
				//make move
			else
				scene->state.moveUnit(unit->getMapX(),unit->getMapY(),toX, toY);
			scene->path.cost=0;
			auto back = scene->path.path.back();
			scene->path.path.clear();
			if(isAttack) {
				scene->state.attack(back.first, back.second, toX, toY);
				scene->focusedUnitIndex=-1;
			}
		}
		else {
			//change unit
			int clickedUnit = findMiniUnit(units, px, py);
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
		scene->focusedUnitIndex = findMiniUnit(units, px, py);
		if (scene->focusedUnitIndex == -1)
			scene->clickPos = {px, py};
	}
}

void front::MouseClickCallback::GameLeftClick(int px, int py) {
	auto units = scene->state.getUnits();
	if (!scene->path.path.empty()) {
		auto &unit = units[scene->focusedUnitIndex];
		auto to = scene->path.path[scene->path.path.size() - 1];
		auto&&[toX, toY] = to;
		if (unit && unit->getMapX() == px && unit->getMapY() == py) {
			scene->path.cost = 0;
			scene->path.path.clear();
		}
		else if (toX == px && toY == py) {
			const Tile &targetTile = scene->state.getMap()[toX][toY];
			bool isAttack = false;
			if (targetTile.unit && targetTile.unit->getOwner() != units[scene->focusedUnitIndex]->getOwner()) {
				isAttack = true;
				if(scene->path.path.size()>1u) {
					scene->path.path.pop_back();
					scene->path = scene->state.getShortestPath(unit->getMapX(), unit->getMapY(),
					                                           scene->path.path.back().first,
					                                           scene->path.path.back().second);
					scene->state.moveUnit(unit->getMapX(), unit->getMapY(), scene->path.path.back().first,
					                      scene->path.path.back().second);
				}
				else {
					scene->path.path={{unit->getMapX(), unit->getMapY()}};
				}
			}
			else
				scene->state.moveUnit(unit->getMapX(), unit->getMapY(), toX, toY);
			scene->path.cost = 0;
			auto back = scene->path.path.back();
			scene->path.path.clear();
			if (isAttack) {
				scene->state.attack(back.first, back.second, toX, toY);
				scene->focusedUnitIndex = -1;
			}
		}
		else {
			//change unit
			int clickedUnit = findUnit(units, px, py);
			if (clickedUnit != -1) {
				scene->focusedUnitIndex = clickedUnit;
				scene->path.cost = 0;
				scene->path.path.clear();
			}
		}
	}
	scene->path.cost = 0;
	scene->path.path.clear();
	if (scene->focusedUnitIndex > -1) {
		auto &unit = units[scene->focusedUnitIndex];
		scene->path = scene->state.getShortestPath(unit->getMapX(), unit->getMapY(), px, py);
	}
	else {
		scene->clickPos = {-1, -1};
		scene->focusedUnitIndex = findUnit(units, px, py);
		if (scene->focusedUnitIndex == -1)
			scene->clickPos = {px, py};
	}
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
		if(scene->state.isInMiniGame())
			MiniGameLeftClick(px,py);
		else
			GameLeftClick(px,py);
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