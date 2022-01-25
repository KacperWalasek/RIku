#pragma once/*
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>*/
#include "TileObjectDecorator.h"
#include "../StateUpdate/Move/UseResources.h"
class UseResourceOnBuild :
    public TileObjectDecorator
{
    int resource;
    int quantity;
    UseResourceOnBuild() :resource(0), quantity(0) {}
    friend cereal::access;
public:
    UseResourceOnBuild(std::shared_ptr<ITileObject> next, int resource, int quantity);

    virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;
    virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(resource, quantity, TileObjectDecorator::next);
    }
};

