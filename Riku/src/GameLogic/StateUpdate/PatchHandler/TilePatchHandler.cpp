#include "TilePatchHandler.h"
#include "../Move/CombinedMove.h"

std::shared_ptr<IMove> TilePatchHandler::handlePatch(GameState& state, const Patch& patch) const
{	
	std::shared_ptr<IMove> move = nullptr;
	for (auto& tilePatch : patch.tilePatches)
	{
		state.map[tilePatch.first.first][tilePatch.first.second].object = tilePatch.second.object;
		if (tilePatch.second.object) 
		{
			auto hookMove = tilePatch.second.object->onBeingPlaced(tilePatch.first.first, tilePatch.first.second);
			move = std::make_shared<CombinedMove>(move, hookMove);
		}
		state.map[tilePatch.first.first][tilePatch.first.second].unit = tilePatch.second.unit;
		if (tilePatch.second.unit)
		{
			auto hookMove = tilePatch.second.unit->onBeingPlaced(tilePatch.first.first, tilePatch.first.second);
			move = std::make_shared<CombinedMove>(move, hookMove);
		}
	}
	return move;
}
