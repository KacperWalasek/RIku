#pragma once
#include "IMiniPatchHandler.h"

class TileMiniPatchHandler :
    public IMiniPatchHandler
{
public:
	virtual void handlePatch(MiniGameState& state, const MiniPatch& patch) const override
	{
		for (auto& tilePatch : patch.tilePatches)
		{
			MiniTile& tile = state.map[tilePatch.first.first][tilePatch.first.second];
			if (tilePatch.second.removeUnit)
				tile.unit = nullptr;
			if (tilePatch.second.unit)
				tile.unit = tilePatch.second.unit;
		}
	}
};

