#include "MiniUnit.h"

MiniUnit::MiniUnit(std::string name, int player, int baseMovementPoints, const std::map<std::string, sol::function>& hooks)
    :name(name), player(player), baseMovementPoints(baseMovementPoints), movementPoints(baseMovementPoints), loadedHookable(hooks)
{}

std::shared_ptr<IMiniMove> MiniUnit::onDestroy(bool byOwner)
{
    return std::shared_ptr<IMiniMove>();
}

std::shared_ptr<IMiniMove> MiniUnit::onTurnEnd()
{
    return std::shared_ptr<IMiniMove>();
}

std::shared_ptr<IMiniMove> MiniUnit::onTurnBegin()
{
    return std::shared_ptr<IMiniMove>();
}

std::shared_ptr<IMiniMove> MiniUnit::onBeingPlaced(int mapX, int mapY)
{
    return std::shared_ptr<IMiniMove>();
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

int MiniUnit::getPlayer() const
{
    return player;
}
