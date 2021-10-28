// Kacper Walasek

#pragma once
#include "ITileObject.h"
#include <memory>
class TileObjectDecorator :
    public ITileObject
{
    std::shared_ptr<ITileObject> next;
public:
    TileObjectDecorator(std::shared_ptr<ITileObject> next) : next(next) {}

    virtual std::string getName() const override { return next->getName(); }

    virtual double getModifiedCost(double cost) const override { return next->getModifiedCost(cost); }

    virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override { return next->onDestroy(byOwner); }

    virtual std::shared_ptr<IMove> onTurnEnd() override { return next->onTurnEnd(); }

    virtual std::shared_ptr<IMove> onTurnBegin() override { return next->onTurnBegin(); }

    virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override { return next->onBeingPlaced(mapX, mapY); };
};
