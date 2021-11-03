// Kacper Walasek
#include "Area.h"

Area::Area(std::string name, double mult)
	: Resource(name), mult(mult > 1 ? mult : 1)
{}

double Area::getModifiedCost(double cost) const
{
	return cost * mult;
}
