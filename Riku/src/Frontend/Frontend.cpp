#include "Frontend.h"

front::Frontend::Frontend(GameLogic& logic)
	: logic(logic), state(logic), window(config,logic,state, assetHandler), assetHandler(state.getAssetHandler())
{
	assetHandler.loadFiles();
}

bool front::Frontend::update()
{
	return window.update();
}
