#pragma once
#include "IMiniPatchHandler.h"
class PlayerMiniPatchHandler :
    public IMiniPatchHandler
{
public:
    virtual std::shared_ptr<IMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const override
    {
        auto& playerUnits = state.player.units;
        auto& enemyUnits = state.enemy.units;
        for (std::shared_ptr<MiniUnit> unit : patch.playerPatch.addedUnits)
            playerUnits.push_back(unit);

        for (std::shared_ptr<MiniUnit> unit : patch.enemyPatch.addedUnits)
            enemyUnits.push_back(unit);

        for (std::shared_ptr<MiniUnit> unit : patch.playerPatch.removedUnits)
        {
            auto unitIt = std::find(playerUnits.begin(), playerUnits.end(), unit);
            if (unitIt != playerUnits.end())
                playerUnits.erase(unitIt);
        }

        for (std::shared_ptr<MiniUnit> unit : patch.enemyPatch.removedUnits)
        {
            auto unitIt = std::find(enemyUnits.begin(), enemyUnits.end(), unit);
            if (unitIt != enemyUnits.end())
                enemyUnits.erase(unitIt);
        }

        return nullptr;
    }
};

