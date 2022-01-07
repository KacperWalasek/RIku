#pragma once
#include "IMiniPatchHandler.h"

namespace minigame
{
    class PlayerMiniPatchHandler :
        public IMiniPatchHandler
    {
        virtual void handlePatchForPlayer(MiniGamePlayer& player, const MiniPlayerPatch& patch) const
        {
            auto& units = player.units;
            for (std::shared_ptr<MiniUnit> unit : patch.addedUnits)
                units.push_back(unit);

            for (std::shared_ptr<MiniUnit> unit : patch.removedUnits)
            {
                auto unitIt = std::find(units.begin(), units.end(), unit);
                if (unitIt != units.end())
                    units.erase(unitIt);
            }

            for (const std::string& removedSkill : patch.usedSkills)
            {
                auto it = std::find(player.skills.begin(), player.skills.end(), removedSkill);
                if (it != player.skills.end())
                    player.skills.erase(it);
            }
        }
    public:
        virtual std::shared_ptr<IMove> handlePatch(MiniGameState& state, const MiniPatch& patch) const override
        {
            handlePatchForPlayer(state.player, patch.playerPatch);
            handlePatchForPlayer(state.enemy, patch.enemyPatch);

            return nullptr;
        }
    };

}