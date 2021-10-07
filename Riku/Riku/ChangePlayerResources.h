//Kacper Walasek
#pragma once
#include "IMove.h"
#include "GameState.h"

class ChangePlayerResources :
    public IMove
{
    int player;
    int resource;
    int quantity;
public:
    ChangePlayerResources(int player, int resource, int quantity);
    virtual std::shared_ptr<Patch> apply(const GameState& state) const override;
    virtual bool isDoable(const GameState& state) const override;
};

