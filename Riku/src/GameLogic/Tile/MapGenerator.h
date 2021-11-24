#pragma once
#include "../Assets/AssetHandler.h"
#include "../LogicAssets.h"
#include "Tile.h"
#include "TileDescription.h"

class MapGenerator
{
	logic::Asset asset;
public:
	MapGenerator(logic::Asset asset);
	std::vector<std::vector<Tile>> getMap(const LogicAssets& assets);
};

