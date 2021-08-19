// Kacper Walasek
#pragma once
#include "ICostModifier.h"
#include "Resource.h"
#include <string>

class Biome : public Resource
{
    int mpCost;
public:
    Biome(std::string name, int mpCost);
    int getCost() const;
};

