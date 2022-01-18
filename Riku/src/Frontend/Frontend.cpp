#include "Frontend.h"
#include "Lang.h"

front::Frontend::Frontend(GameLogic& logic, Config& config)
	: config(config), logic(logic), state(logic), window(config,logic,state, assetHandler), assetHandler(state.getLogicAssetHandler(), state.getMinigameAssetHandler())
{
	assetHandler.loadFiles();

	state.setName("Name");
	state.setHotseatPlayerCount(2);
	state.startGame();
	/*state.invite("192.168.0.14");
	auto invitedPlayers = state.getInvitedPlayers();*/
}

bool front::Frontend::update()
{
	/*auto invitedPlayers = state.getInvitedPlayers();
	if (invitedPlayers.size() > 0 && invitedPlayers.begin()->second.state == InvitationState::Joined && !state.isInGame())
	{
		state.startGame();
		int x =state.getPlayerCount();
	}*/
	return window.update();
}
