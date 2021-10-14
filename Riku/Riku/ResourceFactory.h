//Kacper Walasek
#pragma once
#include "TileObjectDecorator.h"
class ResourceFactory :
    public TileObjectDecorator
{
    int resource;
    int quantity;
public:
    ResourceFactory(std::shared_ptr<ITileObject> next, int resource,int quantity);
    virtual std::shared_ptr<IMove> onTurnEnd() override;
    
};

