//Kacper Walasek
#pragma once
#include "IMove.h"

class RemovePlayerResources :
    public IMove
{
    int player;
    int resource;
    int quantity;
public:
    RemovePlayerResources(int player, int resource, int quantity);
    virtual int apply(GameState& state) const override;
    virtual bool isDoable(const GameState& state) const override;
};

