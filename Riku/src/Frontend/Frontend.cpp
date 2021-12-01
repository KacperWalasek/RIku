#include "Frontend.h"
#include "Lang.h"

front::Frontend::Frontend(GameLogic& logic, Config& config)
	: config(config), logic(logic), state(logic), window(config,logic,state, assetHandler), assetHandler(state.getAssetHandler())
{
	assetHandler.loadFiles();
	Lang::loadLanguage(state.getAssetHandler(), config.language);
}

bool front::Frontend::update()
{
	return window.update();
}
