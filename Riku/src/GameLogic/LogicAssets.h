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
	logic::AssetHandler handler;
	std::map<std::string, Biome> biomes;
	std::map<std::string, Area> areas;
	std::map<std::string, Ground> grounds;
	std::vector<Resource> playerResources;
	std::map<std::string, logic::Asset> tileObjects;
	std::map<std::string, logic::Asset> units;
	logic::Asset mapGenerator;

	void initialize(std::string assetPath);
};
