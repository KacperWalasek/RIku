// Kacper Walasek
#pragma once
#include "ICostModifier.h"
#include "Resource.h"
#include <string>

class Ground :
    public ICostModifier, public Resource
{
    double mult = 0;
public:
    Ground(std::string name, double mult);
    virtual double modifyCost(double cost) const override;
};

