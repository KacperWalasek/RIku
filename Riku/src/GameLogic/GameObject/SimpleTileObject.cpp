// Kacper Walasek

#include "SimpleTileObject.h"

SimpleTileObject::SimpleTileObject(std::string name, const std::map<std::string, sol::function>& hooks, GUIDescription gui) : loadedHookable(hooks), name(name), gui(gui) {}

std::string SimpleTileObject::getName() const
{
	return name;
}

double SimpleTileObject::getModifiedCost(double cost) const
{
	return cost;
}

std::shared_ptr<IMove> SimpleTileObject::onDestroy(bool byOwner)
{
	return loadedHookable.onDestroy(*this,byOwner);
}

std::shared_ptr<IMove> SimpleTileObject::onTurnEnd()
{
	return loadedHookable.onTurnEnd(*this);
}

std::shared_ptr<IMove> SimpleTileObject::onTurnBegin()
{
	return loadedHookable.onTurnBegin(*this);
}

std::shared_ptr<IMove> SimpleTileObject::onBeingPlaced(int mapX, int mapY)
{
	return loadedHookable.onBeingPlaced(*this, mapX, mapY);
}

bool SimpleTileObject::canBeBuilt(const GameState& state, int mapX, int mapY)
{
	return loadedHookable.canBeBuilt(*this, state, mapX, mapY);
}

const GUIDescription& SimpleTileObject::getGuiDescription()
{
	return gui;
}

std::shared_ptr<IMove> SimpleTileObject::onOptionChosen(int index, const LogicAssets& assets)
{
	return gui.onOptionChosen(index, assets);
}
