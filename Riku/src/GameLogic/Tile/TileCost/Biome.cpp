// Kacper Walasek
#include "Biome.h"

Biome::Biome(std::string name, double mult)
	: Resource(name), mult(mult)
{}

double Biome::getModifiedCost(double cost) const
{
	return cost * mult;
}