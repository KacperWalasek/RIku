#pragma once
#include "IPatchHandler.h"
#include "../../../MiniGame/MiniGame.h"
#include "../../GameState.h"
#include "../../Utils/LogicUtils.h"
#include "../../Actions/CombinedAction.h"
#include "../../Actions/SendPatchToAll.h"
#include "../../Actions/ResetCummulatedPatch.h"
#include "../../FrontendCommunicator/Responses/IntResponse.h"
class MiniGamePatchHandler :
    public IPatchHandler
{
public:
    virtual std::shared_ptr<IAction> handlePatch(GameState& state, const Patch& patch) const override
    {
		bool send = false;
		for (auto p : patch.miniGamePatches)
		{
			if (std::find(state.hotSeatPlayers.begin(), state.hotSeatPlayers.end(), p.second.player) == state.hotSeatPlayers.end())
			{
				send = true;
				continue;
			}
			if (p.second.remove)
			{
				// TODO sprawdzic czy to sie wywali jak player nie bedzie w trakcie minigry
				auto minigameIt = state.minigames.find(p.first);
				if (minigameIt != state.minigames.end())
				{
					auto odp = minigameIt->second->getInfo(std::make_shared<Request>("winner"));
					auto intOdp = std::static_pointer_cast<IntResponse>(odp);
					LogicUtils::addPopup("Player " + std::to_string(intOdp->get()) + " won minigame!");
					state.minigames.erase(p.first);
				}
			}
			else
			{
				auto minigameIt = state.minigames.find(p.first);
				if (minigameIt == state.minigames.end())
				{
					auto minigame = std::make_shared<minigame::MiniGame>(
						*(std::dynamic_pointer_cast<Unit>(LogicUtils::getHookable(p.second.playerUnit))),
						*(std::dynamic_pointer_cast<Unit>(LogicUtils::getHookable(p.second.enemyUnit))),
						p.second.isBegining);
					state.minigames.emplace(p.first, minigame);
					minigameIt = state.minigames.find(p.first);
				}
				if (p.second.miniPatch)
				{
					// TODO:webModule if enemy on same pc
					minigameIt->second->applyMiniPatch(p.second.miniPatch);
					// else return SendMiniPatch
				}
				if (p.second.resetCummulatedPatch)
					minigameIt->second->resetCummulatedPatch();
			}
		}

		return send ? std::make_shared<CombinedAction>(
			std::make_shared<SendPatchToAll>(),
			std::make_shared<ResetCummulatedPatch>()) : nullptr;
    }
};

