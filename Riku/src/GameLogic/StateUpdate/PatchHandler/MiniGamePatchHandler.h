#pragma once
#include "IPatchHandler.h"
#include "../../../MiniGame/MiniGame.h"
#include "../../GameState.h"
class MiniGamePatchHandler :
    public IPatchHandler
{
public:
    virtual std::shared_ptr<IAction> handlePatch(GameState& state, const Patch& patch) const override
    {
		for (auto p : patch.miniGamePatches)
		{
			if (p.second.remove)
				// TODO sprawdzic czy to sie wywali jak player nie bedzie w trakcie minigry
				state.minigames.erase(p.first);
			else
			{
				auto minigameIt = state.minigames.find(p.first);
				if (minigameIt == state.minigames.end())
				{
					auto minigame = std::make_shared<minigame::MiniGame>(p.first, p.second.enemy, p.second.isBegining);
					state.minigames.emplace(p.first, minigame);
					minigameIt = state.minigames.find(p.first);
				}
				if(p.second.miniPatch)
					minigameIt->second->applyMiniPatch(p.second.miniPatch);
				if (p.second.resetCummulatedPatch)
					minigameIt->second->resetCummulatedPatch();
			}
		}
		return nullptr;
    }
};

