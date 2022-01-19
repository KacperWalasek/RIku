#pragma once
#include "IPatchHandler.h"
class WinnerPatchHandler :
    public IPatchHandler
{
public:
    virtual std::shared_ptr<IAction> handlePatch(GameState& state, const Patch& patch) const override;
};

