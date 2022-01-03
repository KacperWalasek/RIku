#include "Frontend.h"
#include "Lang.h"

front::Frontend::Frontend(GameLogic& logic, Config& config)
	: config(config), logic(logic), state(logic), window(config,logic,state, assetHandler), assetHandler(state.getAssetHandler())
{
	assetHandler.loadFiles();

	int p = state.getPlayerOnMove();
	bool x = state.isInMiniGame();
	state.attack(11, 10, 12, 10);
	x = state.isInMiniGame();
	auto path = state.getShortestPath(1, 2, 10, 10);
	auto m = state.getMiniMap();
	state.moveUnit(1, 2, 3, 3);
	m = state.getMiniMap();
	//state.attack(3, 3, 2, 2);
	m = state.getMiniMap();
	state.finishTurn();
	x = state.isInMiniGame();
	p = state.getPlayerOnMove();
	m = state.getMiniMap();
	state.moveUnit(2, 2, 4, 4);
	m = state.getMiniMap();
	state.finishTurn();
	p = state.getPlayerOnMove();
}

bool front::Frontend::update()
{
	return window.update();
}
