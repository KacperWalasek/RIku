#pragma once
#include "IPatchHandler.h"
// TODO change this after changing MiniGame to interface if possible
#include "../../../MiniGame/MiniGame.h"
#include "../../GameState.h"
class MiniGamePatchHandler :
    public IPatchHandler
{
public:
    virtual std::shared_ptr<IMove> handlePatch(GameState& state, const Patch& patch) const override 
    {
		for (auto p : patch.miniGamePatches)
		{
			if (p.second.remove)
				// TODO sprawdzic czy to sie wywali jak player nie bedzie w trakcie minigry
				state.minigames.erase(p.first);
			else
			{
				MiniGame minigame(p.first, p.second.enemy, p.second.isBegining);
				state.minigames.emplace(p.first, minigame);
			}
		}
		return nullptr;
    }
};

