// Kacper Walasek
#pragma once
#include "ICostModifier.h"
#include "Resource.h"
#include <string>

class Area :
    public ICostModifier, public Resource
{
    double mult;
public:
    Area(std::string name, double mult);
    virtual double modifyCost(double cost) const override;
};

