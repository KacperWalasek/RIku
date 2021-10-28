//Kacper Walasek
#pragma once
#include "TileObjectDecorator.h"
class ResourceFactory :
    public TileObjectDecorator
{
    int resource;
    int quantity;
    int mapX = -1;
    int mapY = -1;
public:
    ResourceFactory(std::shared_ptr<ITileObject> next, int resource, int quantity);
    virtual std::shared_ptr<IMove> onTurnEnd() override;
    virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;
};

