// Kacper Walasek

#pragma once
#include "ITileObject.h"
#include <memory>
#include "../GameState.h"
#include <cereal/access.hpp>

class TileObjectDecorator :
    public ITileObject
{
protected:
    std::shared_ptr<ITileObject> next;
    TileObjectDecorator() {};
    friend cereal::access;
public:
    TileObjectDecorator(std::shared_ptr<ITileObject> next) : next(next) {}

    virtual std::string getName() const override { return next->getName(); }

    virtual double getModifiedCost(double cost) const override { return next->getModifiedCost(cost); }

    virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override { return next->onDestroy(byOwner); }

    virtual std::shared_ptr<IMove> onTurnEnd() override { return next->onTurnEnd(); }

    virtual std::shared_ptr<IMove> onTurnBegin() override { return next->onTurnBegin(); }

    virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override { return next->onBeingPlaced(mapX, mapY); }

    virtual std::shared_ptr<IMove> onBeingCreated() override { return next->onBeingCreated(); }

    virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) { return next->canBeBuilt(state, mapX, mapY); }

    virtual const GUIDescription& getGuiDescription() override { return next->getGuiDescription(); };

    virtual std::shared_ptr<IMove> onOptionChosen(int index, int mapX, int mapY) override { return next->onOptionChosen(index, mapX, mapY); };

    virtual int getOwner() const override { return next->getOwner(); }

    virtual std::string getId() const override { return next->getId(); }

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(next);
    }
};
