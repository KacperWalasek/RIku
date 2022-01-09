#include "MiniUnit.h"
#include "../../GameLogic/Utils/LogicUtils.h"

minigame::MiniUnit::MiniUnit(std::string name, int owner, int baseMovementPoints, const std::map<std::string, sol::function>& hooks)
    :name(name), owner(owner), baseMovementPoints(baseMovementPoints), movementPoints(baseMovementPoints), loadedHookable(hooks), id(LogicUtils::getUniqueId())
{}

std::shared_ptr<minigame::IMiniMove> minigame::MiniUnit::onDestroy(bool byOwner)
{
    return loadedHookable.onDestroy(*this,byOwner);
}

std::shared_ptr<minigame::IMiniMove> minigame::MiniUnit::onTurnEnd()
{
    return loadedHookable.onTurnEnd(*this);
}

std::shared_ptr<minigame::IMiniMove> minigame::MiniUnit::onTurnBegin()
{
    return loadedHookable.onTurnBegin(*this);
}

std::shared_ptr<minigame::IMiniMove> minigame::MiniUnit::onBeingPlaced(int mapX, int mapY)
{

    return loadedHookable.onBeingPlaced(*this,mapX,mapY);
}

std::string minigame::MiniUnit::getName() const
{
    return name;
}

int minigame::MiniUnit::getMapX() const
{
    return mapX;
}

int minigame::MiniUnit::getMapY() const
{
    return mapY;
}

int minigame::MiniUnit::getOwner() const
{
    return owner;
}

std::string minigame::MiniUnit::getId() const
{
    return id;
}
