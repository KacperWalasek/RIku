#pragma once
#include "IPatchHandler.h"
#include "../../GameState.h"

class ClearPatchHandler :
    public IPatchHandler
{
public:
    virtual std::shared_ptr<IAction> handlePatch(GameState& state, const Patch& patch) const override;
};


