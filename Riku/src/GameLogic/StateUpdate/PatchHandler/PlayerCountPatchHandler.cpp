#include "PlayerCountPatchHandler.h"

PlayerCountPatchHandler::PlayerCountPatchHandler(const LogicAssets& assets)
	: assets(assets)
{
}

std::shared_ptr<IAction> PlayerCountPatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
	if (patch.playerCount > 0)
	{
		state.players = {};
		for (int i = 0; i < patch.playerCount; i++)
			state.players.emplace_back(assets.playerResources.size());
	}
	return nullptr;
}
