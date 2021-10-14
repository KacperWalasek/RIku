#pragma once
#include "IPatchHandler.h"
class PlayerPatchHandler :
    public IPatchHandler
{
public:
    virtual void handlePatch(GameState& state, const Patch& patch) const override;
};

