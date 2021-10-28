// Kacper Walasek
#pragma once

class ICostModifier
{
public:
	virtual double getModifiedCost(double cost) const = 0;
};

