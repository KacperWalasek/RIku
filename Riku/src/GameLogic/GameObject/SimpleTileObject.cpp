// Kacper Walasek

#include "SimpleTileObject.h"
#include "../StateUpdate/Move/CombinedMove.h"
#include "../Utils/LogicUtils.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>
SimpleTileObject::SimpleTileObject(std::string name, int player, const std::map<std::string, sol::function>& hooks, GUIDescription gui, std::string id)
	: loadedHookable(hooks), name(name), player(player), gui(gui), id(id=="" ? LogicUtils::getUniqueId() : id) {}

std::string SimpleTileObject::getName() const
{
	return name;
}

int SimpleTileObject::getOwner() const
{
	return player;
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

std::shared_ptr<IMove> SimpleTileObject::onBeingCreated()
{
	return loadedHookable.onBeingCreated(*this);
}

bool SimpleTileObject::canBeBuilt(const GameState& state, int mapX, int mapY)
{
	return loadedHookable.canBeBuilt(*this, state, mapX, mapY);
}

const GUIDescription& SimpleTileObject::getGuiDescription()
{
	return gui;
}

std::shared_ptr<IMove> SimpleTileObject::onOptionChosen(int index, int mapX, int mapY)
{
	return gui.onOptionChosen(index, mapX, mapY);
}

std::string SimpleTileObject::getId() const
{
	return id;
}


CEREAL_REGISTER_TYPE(SimpleTileObject);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ITileObject, SimpleTileObject)