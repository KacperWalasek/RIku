// Kacper Walasek
#pragma once
#include <vector>
#include "Tile/TileCost/Biome.h"
#include "Tile/TileCost/Area.h"
#include "Tile/TileCost/Ground.h"
#include "Assets/AssetHandler.h"

struct LogicAssets
{
	std::vector<Biome> biomes;
	std::vector<Area> areas;
	std::vector<Ground> grounds;
	std::vector<Resource> playerResources;
	void initialize();
};
