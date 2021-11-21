#include "TilePatchHandler.h"

void TilePatchHandler::handlePatch(GameState& state, const Patch& patch) const
{	
	for (auto& tilePatch : patch.tilePatches)
	{
		state.map[tilePatch.first.first][tilePatch.first.second].object = tilePatch.second.object;
		if(tilePatch.second.object)
			tilePatch.second.object->onBeingPlaced(tilePatch.first.first, tilePatch.first.second);
		state.map[tilePatch.first.first][tilePatch.first.second].unit = tilePatch.second.unit;
		if (tilePatch.second.unit)
			tilePatch.second.unit->onBeingPlaced(tilePatch.first.first, tilePatch.first.second);
	}
}
