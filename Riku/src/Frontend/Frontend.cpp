#include "Frontend.h"
#include "Lang.h"
#include "Window/LoadingWindow.h"
#include <future>

front::Frontend::Frontend(GameLogic& logic, Config& config)
	: config(config), logic(logic), state(logic), window(config,logic,state, assetHandler), assetHandler(state.getLogicAssetHandler(), state.getMinigameAssetHandler())
{
	//LoadingWindow loading;
	//loading.update();
	assetHandler.loadFiles(); 

	window.show();
	//loading.destroy();
}

bool front::Frontend::update()
{
	return window.update();
}
