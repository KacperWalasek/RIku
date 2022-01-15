//Kacper Walasek
#include "PlayerPatchHandler.h"
#include "../../Utils/LogicUtils.h"

std::shared_ptr<IAction> PlayerPatchHandler::handlePatch(GameState& state, const Patch& patch) const
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
		for (std::shared_ptr<Unit> unit : p.second.addedUnits)
		{
			player.addUnit(unit);
			LogicUtils::addHookable(unit);
		}
		for (const std::string& unit : p.second.removedUnits)
			player.removeUnit(std::dynamic_pointer_cast<Unit>(LogicUtils::getHookable(unit)));
	}
	return nullptr;
}
