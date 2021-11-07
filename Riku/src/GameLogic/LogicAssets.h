// Kacper Walasek
#pragma once
#include <vector>
#include "Tile/TileCost/Biome.h"
#include "Tile/TileCost/Area.h"
#include "Tile/TileCost/Ground.h"
#include "Assets/AssetHandler.h"
#include "Assets/Asset.h"

struct LogicAssets
{
	std::vector<Biome> biomes;
	std::vector<Area> areas;
	std::vector<Ground> grounds;
	std::vector<Resource> playerResources;
	std::map<std::string, logic::Asset> tileObjects;
	//TODO inicjalizacja z pliku
	void initialize();
};
