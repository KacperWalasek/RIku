#include "TilePatchHandler.h"
#include "../Move/CombinedMove.h"

std::shared_ptr<IMove> TilePatchHandler::handlePatch(GameState& state, const Patch& patch) const
{	
	std::shared_ptr<IMove> move = nullptr;
	for (auto& tilePatch : patch.tilePatches)
	{
		Tile& tile = state.map[tilePatch.first.first][tilePatch.first.second];
		if (tilePatch.second.removeObject)
			tile.object = nullptr;
		if (tilePatch.second.object)
		{
			tile.object = tilePatch.second.object;
			auto hookMove = tilePatch.second.object->onBeingPlaced(tilePatch.first.first, tilePatch.first.second);
			move = std::make_shared<CombinedMove>(move, hookMove);
		}
		if (tilePatch.second.removeUnit)
			tile.unit = nullptr;
		if (tilePatch.second.unit)
		{
			tile.unit = tilePatch.second.unit;
			auto hookMove = tilePatch.second.unit->onBeingPlaced(tilePatch.first.first, tilePatch.first.second);
			move = std::make_shared<CombinedMove>(move, hookMove);
		}
	}
	return move;
}
