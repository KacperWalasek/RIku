#pragma once
#include "TileObjectDecorator.h"
#include "../StateUpdate/Move/UseResources.h"
class UseResourceOnBuild :
    public TileObjectDecorator
{
    int resource;
    int quantity;
public:
    UseResourceOnBuild(std::shared_ptr<ITileObject> next, int resource, int quantity);

    virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;
    virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;
};

