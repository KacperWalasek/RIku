// Kacper Walasek
#include "Ground.h"

Ground::Ground(std::string name, int cost)
	: Resource(name), mpCost(cost)
{}

int Ground::getCost() const
{
	return mpCost;
}

