// Kacper Walasek
#pragma once
#include <vector>
#include "Biome.h"
#include "Area.h"
#include "Ground.h"

struct LogicResources
{
	std::vector<Biome> biomes;
	std::vector<Area> areas;
	std::vector<Ground> grounds;

	//TODO inicjalizacja z pliku
	void initialize();
};

