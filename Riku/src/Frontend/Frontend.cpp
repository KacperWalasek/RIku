#include "Frontend.h"

front::Frontend::Frontend(GameLogic& logic)
	: logic(logic), state(logic), scene(config,logic,state)
{}

bool front::Frontend::update()
{
	return scene.update();
}
