//Kacper Walasek
#pragma once
#include "../Resource.h"
#include "ITileObject.h"
#include "../Hooks/LoadedHookable.h"
#include <map>
#include "../GameState.h"
#include "../Hooks/GUIDescription.h"

class SimpleTileObject : public ITileObject
{
	std::string id;

	LoadedHookable loadedHookable;
 	std::string name;
	int player;
public:
	GUIDescription gui;
	SimpleTileObject(std::string name, int player, const std::map<std::string, sol::function>& hooks, GUIDescription gui);

	virtual std::string getName() const override;
	virtual int getOwner() const override;
	virtual double getModifiedCost(double cost) const override;

	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override;
	virtual std::shared_ptr<IMove> onTurnEnd() override;
	virtual std::shared_ptr<IMove> onTurnBegin() override;
	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;
	virtual std::shared_ptr<IMove> onBeingCreated() override;
	virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;

	virtual const GUIDescription& getGuiDescription() override;
	virtual std::shared_ptr<IMove> onOptionChosen(int index, int mapX, int mapY) override;

	virtual std::string getId() const override;
};

