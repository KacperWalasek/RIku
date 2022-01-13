#pragma once
#include "IPatchHandler.h"
class MapPatchHandler :
    public IPatchHandler
{
    const LogicAssets& assets;
public:
    MapPatchHandler(const LogicAssets& assets);
    virtual std::shared_ptr<IAction> handlePatch(GameState& state, const Patch& patch) const override;
};

