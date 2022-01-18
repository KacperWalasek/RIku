#include "Frontend.h"
#include "Lang.h"

front::Frontend::Frontend(GameLogic& logic, Config& config)
	: config(config), logic(logic), state(logic), window(config,logic,state, assetHandler), assetHandler(state.getLogicAssetHandler(), state.getMinigameAssetHandler())
{
	assetHandler.loadFiles();
}

bool front::Frontend::update()
{
	std::cout << "winner: " << state.getWinner() << std::endl;
	return window.update();
}
