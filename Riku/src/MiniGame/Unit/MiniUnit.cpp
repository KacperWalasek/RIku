#include "MiniUnit.h"

MiniUnit::MiniUnit(std::string name, int owner, int baseMovementPoints, const std::map<std::string, sol::function>& hooks)
    :name(name), owner(owner), baseMovementPoints(baseMovementPoints), movementPoints(baseMovementPoints), loadedHookable(hooks)
{}

std::shared_ptr<IMiniMove> MiniUnit::onDestroy(bool byOwner)
{
    return loadedHookable.onDestroy(*this,byOwner);
}

std::shared_ptr<IMiniMove> MiniUnit::onTurnEnd()
{
    return loadedHookable.onTurnEnd(*this);
}

std::shared_ptr<IMiniMove> MiniUnit::onTurnBegin()
{
    return loadedHookable.onTurnBegin(*this);
}

std::shared_ptr<IMiniMove> MiniUnit::onBeingPlaced(int mapX, int mapY)
{

    return loadedHookable.onBeingPlaced(*this,mapX,mapY);
}

std::string MiniUnit::getName() const
{
    return name;
}

int MiniUnit::getMapX() const
{
    return mapX;
}

int MiniUnit::getMapY() const
{
    return mapY;
}

int MiniUnit::getOwner() const
{
    return owner;
}
