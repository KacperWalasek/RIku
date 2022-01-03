#include "Frontend.h"
#include "Lang.h"

front::Frontend::Frontend(GameLogic& logic, Config& config)
	: config(config), logic(logic), state(logic), window(config,logic,state, assetHandler), assetHandler(state.getAssetHandler())
{
	assetHandler.loadFiles();
	state.attack(11, 10, 12, 10);
	auto units = state.getMiniUnits();
}

bool front::Frontend::update()
{
	return window.update();
}
