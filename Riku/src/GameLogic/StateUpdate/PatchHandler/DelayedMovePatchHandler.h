#pragma once
#include "IPatchHandler.h"
class DelayedMovePatchHandler :
    public IPatchHandler
{
public:
    virtual std::shared_ptr<IAction> handlePatch(GameState& state, const Patch& patch) const override;
};

