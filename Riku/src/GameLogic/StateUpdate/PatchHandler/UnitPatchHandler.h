#pragma once
#include "IPatchHandler.h"
class UnitPatchHandler :
    public IPatchHandler
{
public:
    virtual std::shared_ptr<IMove> handlePatch(GameState& state, const Patch& patch) const override;

};
