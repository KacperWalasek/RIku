#include "Hero.h"

Hero::Hero(int baseMovementPoints, std::string name, int player, const std::map<std::string, sol::function>& hooks)
    : Unit("hero", name, player, baseMovementPoints, hooks), lvl(0), exp(0)
{}

std::shared_ptr<IMove> Hero::onDestroy([[maybe_unused]]bool byOwner)
{
    return std::shared_ptr<IMove>();
}

std::shared_ptr<IMove> Hero::onTurnEnd()
{
    return std::shared_ptr<IMove>();
}

std::shared_ptr<IMove> Hero::onTurnBegin()
{
    return std::shared_ptr<IMove>();
}

std::shared_ptr<IMove> Hero::onBeingPlaced([[maybe_unused]]int mapX, [[maybe_unused]]int mapY)
{
    return std::shared_ptr<IMove>();
}
