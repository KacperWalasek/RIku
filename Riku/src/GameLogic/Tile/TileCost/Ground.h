// Kacper Walasek
#pragma once
#include "ICostModifier.h"
#include "../../Resource.h"
#include <string>

class Ground : public Resource
{
    int mpCost;
public:
    Ground(std::string name, int mpCost);
    int getCost() const;
};

