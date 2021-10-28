//Kacper Walasek
#pragma once
#include "../Resource.h"
#include "ITileObject.h"
#include <map>

class SimpleTileObject : public ITileObject
{
	std::string name;
public: 
	SimpleTileObject(std::string name);
	
	virtual double getModifiedCost(double cost) const override;

	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override { return nullptr; }

	virtual std::shared_ptr<IMove> onTurnEnd() override { return nullptr; }

	virtual std::shared_ptr<IMove> onTurnBegin() override { return nullptr; }

	virtual std::string getName() const override;

	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override { return nullptr; };

};

