#include "Unit.h"


Unit::Unit(std::string type, std::string name, int baseMovementPoints, const std::map<std::string, sol::function>& hooks)
	: type(type), name(name), loadedHookable(hooks), baseMovementPoints(baseMovementPoints), movementPoints(baseMovementPoints)
{}

void Unit::useMovementPoints(int points)
{
	movementPoints -= points;
	if (movementPoints < 0)
		movementPoints = 0;
}

void Unit::restoreMovementPoints()
{
	movementPoints = baseMovementPoints;
}

std::shared_ptr<IMove> Unit::onDestroy(bool byOwner)
{
	return loadedHookable.onDestroy(*this, byOwner);
}

std::shared_ptr<IMove> Unit::onTurnEnd()
{
	return loadedHookable.onTurnEnd(*this);
}

std::shared_ptr<IMove> Unit::onTurnBegin()
{
	return loadedHookable.onTurnBegin(*this);
}

std::shared_ptr<IMove> Unit::onBeingPlaced(int mapX, int mapY)
{
	return loadedHookable.onBeingPlaced(*this, mapX, mapY);
}

std::string Unit::getName() const
{
	return name;
}