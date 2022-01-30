#include "MapPatchHandler.h"

MapPatchHandler::MapPatchHandler(const LogicAssets& assets)
	: assets(assets)
{
}

std::shared_ptr<IAction> MapPatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
    if (patch.map.size() == 0)
        return nullptr;
	state.map.clear();
	for (const auto& descRow : patch.map)
	{
		std::vector<Tile> tileRow;
		for (const auto& desc : descRow)
			tileRow.push_back(Tile(desc.height, assets.areas.at(desc.area), assets.grounds.at(desc.ground), assets.biomes.at(desc.biome)));
		state.map.push_back(tileRow);
	}
    return nullptr;
}
