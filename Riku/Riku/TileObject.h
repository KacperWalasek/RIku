//Kacper Walasek
#pragma once
#include "Resource.h"
#include "ICostModifier.h"
#include <map>

class TileObject : public Resource, public ICostModifier
{
public: 
	TileObject(std::string name);
	// Odziedziczono za pośrednictwem elementu ICostModifier
	virtual double getModifiedCost(double cost) const override;

	// Wywoływane po zniszczeniu obiektu
	virtual std::map<int, int> dropResources() const;

	/*
		TODO - otrzymywanie obrażeń
	*/
};

