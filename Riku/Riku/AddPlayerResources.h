//Kacper Walasek
#pragma once
#include "IMove.h"

class AddPlayerResources :
    public IMove
{
    int player;
    int resource;
    int quantity;
public:
    AddPlayerResources(int player, int resource, int quantity);
    virtual int apply(GameState& state) const override;
    virtual bool isDoable(const GameState& state) const override;
};

