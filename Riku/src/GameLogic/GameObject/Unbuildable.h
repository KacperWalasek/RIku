#pragma once
#include "TileObjectDecorator.h"
class Unbuildable :
    public TileObjectDecorator
{
public:
    Unbuildable(std::shared_ptr<ITileObject> next) : TileObjectDecorator(next) {}
    virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;
};

