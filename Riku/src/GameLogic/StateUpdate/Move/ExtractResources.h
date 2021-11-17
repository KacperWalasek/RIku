//Kacper Walasek
#pragma once
#include "IMove.h"
#include "../../GameState.h"
#include "../Patch/Patch.h"
class ExtractResources :
    public IMove
{
    int player;
    int resource;
    int requiredResource;
    int quantity;
    int mapX;
    int mapY;
public:
    // requireResource<0 => require no resources
    ExtractResources(int player, int resource, int quantity, int mapX, int mapY, int requiredResource = -1);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state) const override;
    virtual bool isDoable(const GameState& state) const override;
};

