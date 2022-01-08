#include "TilePatchHandler.h"
#include "../Move/CombinedMove.h"
#include "../../Unit/Unit.h"
#include "../../Utils/LogicUtils.h"

std::shared_ptr<IAction> TilePatchHandler::handlePatch(GameState& state, const Patch& patch) const
{	
	for (auto& tilePatch : patch.tilePatches)
	{
		Tile& tile = state.map[tilePatch.first.first][tilePatch.first.second];
		if (tilePatch.second.removeObject)
		{
			LogicUtils::removeHookable(tilePatch.second.object->getId());
			tile.object = nullptr;
		}
		if (tilePatch.second.object)
		{
			tile.object = tilePatch.second.object;
			LogicUtils::addHookable(tilePatch.second.object);
		}
		if (tilePatch.second.removeUnit)
			tile.unit = nullptr;
		if (tilePatch.second.unit != "")
			tile.unit = LogicUtils::getHookable(tilePatch.second.unit);
	}
	return nullptr;
}
