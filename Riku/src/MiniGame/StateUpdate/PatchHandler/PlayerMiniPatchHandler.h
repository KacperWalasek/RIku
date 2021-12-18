#pragma once
#include "IMiniPatchHandler.h"
class PlayerMiniPatchHandler :
    public IMiniPatchHandler
{
public:
    virtual void handlePatch(MiniGameState& state, const MiniPatch& patch) const override
    {
        for (std::shared_ptr<MiniUnit> unit : patch.playerPatch.addedUnits)
            state.player.units.push_back(unit);

        for (std::shared_ptr<MiniUnit> unit : patch.enemyPatch.addedUnits)
            state.enemy.units.push_back(unit);
    }
};

