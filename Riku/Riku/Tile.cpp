// Kacper Walasek
#include "Tile.h"

Tile::Tile(int height, const Area& area, const Ground& ground, const Biome& biome)
	: height(height), area(area), ground(ground), biome(biome)
{}

double Tile::getCost() const
{
	return area.modifyCost(ground.modifyCost(biome.getCost()));
}
