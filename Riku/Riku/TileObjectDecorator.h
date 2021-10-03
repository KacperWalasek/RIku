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
    virtual void onDestroy(bool byOwner) override { return next->onDestroy(byOwner); }
    virtual void onTurnEnd() override { return next->onTurnEnd(); }
    virtual void onTurnBegin() override { return next->onTurnBegin(); }
};

