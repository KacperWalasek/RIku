#pragma once
/*#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>*/
#include "TileObjectDecorator.h"
#include "../GameState.h"

class RequireResources :
    public TileObjectDecorator
{
    int resource;
    RequireResources() :resource(0) {}
    friend cereal::access;
public:
    RequireResources(std::shared_ptr<ITileObject> next, int resource);
    virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(resource, TileObjectDecorator::next);
    }
};

