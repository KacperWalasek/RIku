//Kacper Walasek
#pragma once
#include "IPatchHandler.h"
class PlayerPatchHandler :
    public IPatchHandler
{
public:
    virtual std::shared_ptr<IMove> handlePatch(GameState& state, const Patch& patch) const override;
};

