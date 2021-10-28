// Kacper Walasek

#include "SimpleTileObject.h"

SimpleTileObject::SimpleTileObject(std::string name) : name(name) {}

double SimpleTileObject::getModifiedCost(double cost) const
{
	return cost;
}

std::string SimpleTileObject::getName() const
{
	return name;
}
