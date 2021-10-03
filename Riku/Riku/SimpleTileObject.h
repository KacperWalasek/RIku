//Kacper Walasek
#pragma once
#include "Resource.h"
#include "ITileObject.h"
#include <map>

class SimpleTileObject : public ITileObject
{
	std::string name;
public: 
	SimpleTileObject(std::string name);

	virtual double getModifiedCost(double cost) const override;

	virtual void onDestroy(bool byOwner) override {};

	virtual void onTurnEnd() override {};

	virtual void onTurnBegin() override {};

	virtual std::string getName() const override;

};

