// Kacper Walasek
#pragma once
#include <memory>
#include "TileCost/Area.h"
#include "TileCost/Ground.h"
#include "TileCost/Biome.h"
#include "../GameObject/ITileObject.h"

class Tile
{
public:
	Tile(int height, const Area& area, const Ground& ground, const Biome& biome, int resource = -1);

	int height;
	const Area& area;
	const Ground& ground;
	const Biome& biome;

	double getCost() const;

	std::shared_ptr<ITileObject> object;
	int resource; // -1 for no resource
};

