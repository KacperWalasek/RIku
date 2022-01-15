#pragma once
#include "IPatchHandler.h"
class PlayerCountPatchHandler :
    public IPatchHandler
{
    const LogicAssets& assets;
public:
    PlayerCountPatchHandler(const LogicAssets& assets);
    virtual std::shared_ptr<IAction> handlePatch(GameState& state, const Patch& patch) const override;
};

