//Kacper Walasek
#pragma once
/*#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>*/
#include "TileObjectDecorator.h"
class ResourceFactory :
    public TileObjectDecorator
{
    int resource = 0;
    int quantity = 0;
    int mapX = -1;
    int mapY = -1;
    ResourceFactory() : TileObjectDecorator(nullptr) {};
    friend cereal::access;
public:
    ResourceFactory(std::shared_ptr<ITileObject> next, int resource, int quantity);
    virtual std::shared_ptr<IMove> onTurnEnd(int mapX, int mapY) override;
    virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(resource, quantity, mapX, mapY, TileObjectDecorator::next);
    }
};

