// Kacper Walasek
#include "Biome.h"

Biome::Biome(std::string name, int cost)
	: Resource(name), mpCost(cost)
{}

int Biome::getCost() const
{
	return mpCost;
}
