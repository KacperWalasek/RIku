// Kacper Walasek
#pragma once
#include "ICostModifier.h"
#include "../../Resource.h"
#include <string>

class Biome :
    public ICostModifier, public Resource
{
    double mult = 0;
public:
    Biome(std::string name, double mult);
    virtual double getModifiedCost(double cost) const override;
};

