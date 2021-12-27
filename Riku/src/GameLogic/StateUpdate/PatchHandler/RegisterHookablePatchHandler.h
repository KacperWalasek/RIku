#pragma once
#include "IPatchHandler.h"
#include "../../GameState.h"

class RegisterHookablePatchHandler :
    public IPatchHandler
{
public:
    virtual std::shared_ptr<IMove> handlePatch(GameState& state, const Patch& patch) const override;
};

