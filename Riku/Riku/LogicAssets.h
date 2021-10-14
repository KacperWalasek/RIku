// Kacper Walasek
#pragma once
#include <vector>
#include "Biome.h"
#include "Area.h"
#include "Ground.h"

struct LogicAssets
{
	std::vector<Biome> biomes;
	std::vector<Area> areas;
	std::vector<Ground> grounds;
	std::vector<Resource> playerResources;

	//TODO inicjalizacja z pliku
	void initialize();
};

