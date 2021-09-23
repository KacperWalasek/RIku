#include "TileObject.h"

TileObject::TileObject(std::string name): Resource(name) {}

double TileObject::getModifiedCost(double cost) const
{
    return cost;
}

std::map<int, int> TileObject::dropResources() const
{
    return std::map<int, int>();
}
