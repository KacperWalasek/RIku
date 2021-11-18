#include "Hero.h"

Hero::Hero(int baseMovementPoints, std::string name, const std::map<std::string, sol::function>& hooks)
    : Unit("hero", name, baseMovementPoints, hooks), exp(0), lvl(0)
{}

std::shared_ptr<IMove> Hero::onDestroy(bool byOwner)
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

std::shared_ptr<IMove> Hero::onBeingPlaced(int mapX, int mapY)
{
    return std::shared_ptr<IMove>();
}
