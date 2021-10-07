#include "PlayerPatchHandler.h"

void PlayerPatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
	for (auto p : patch.playerPatches)
	{
		Player& player = state.players[p.first];
		for (const std::pair<int, int> resourceChange : p.second.resourceChanges) 
		{
			if (resourceChange.second < 0)
				player.useResources(resourceChange.first, -resourceChange.second);
			else
				player.acceptResources(resourceChange.first, resourceChange.second);
		}
	}
}
