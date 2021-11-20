//Kacper Walasek
#pragma once
#include "../Resource.h"
#include "ITileObject.h"
#include "../LoadedHookable.h"
#include <map>

class SimpleTileObject : public ITileObject
{
	LoadedHookable loadedHookable;
 	std::string name;
public: 
	SimpleTileObject(std::string name, const std::map<std::string, sol::function>& hooks);

	virtual std::string getName() const override;
	virtual double getModifiedCost(double cost) const override;

	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override;
	virtual std::shared_ptr<IMove> onTurnEnd() override;
	virtual std::shared_ptr<IMove> onTurnBegin() override;
	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;
};

