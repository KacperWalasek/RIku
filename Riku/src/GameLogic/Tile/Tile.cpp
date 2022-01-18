// Kacper Walasek
#include "Tile.h"

Tile::Tile(int height, const Area& area, const Ground& ground, const Biome& biome, int resource)
	: height(height), area(area), ground(ground), biome(biome), resource(resource)
{}
double Tile::getCost() const
{
	return area.getModifiedCost(biome.getModifiedCost(ground.getCost()));
}
