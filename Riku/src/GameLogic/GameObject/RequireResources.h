#pragma once
#include "TileObjectDecorator.h"
#include "../GameState.h"

class RequireResources :
    public TileObjectDecorator
{
    int resource;
public:
    RequireResources(std::shared_ptr<ITileObject> next, int resource);
    virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;
};

