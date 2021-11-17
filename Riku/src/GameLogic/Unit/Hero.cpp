#include "Hero.h"

Hero::Hero(int baseMovementPoints, std::string name) : Unit("hero", name, baseMovementPoints, {}), exp(0), lvl(0)
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
