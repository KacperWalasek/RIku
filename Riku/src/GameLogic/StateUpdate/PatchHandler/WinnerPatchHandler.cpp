#include "WinnerPatchHandler.h"
#include "../../Actions/CombinedAction.h"
#include "../../Actions/SendPatchToAll.h"
#include "../../Actions/ResetCummulatedPatch.h"
#include "../../Utils/LogicUtils.h"

std::shared_ptr<IAction> WinnerPatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
    if (patch.winner != -1)
    {
        state.winner = patch.winner;
        LogicUtils::addPopup("Player " + std::to_string(state.winner) + " won the game!");
		return std::make_shared<CombinedAction>(
				std::make_shared<SendPatchToAll>(),
				std::make_shared<ResetCummulatedPatch>());
    }
    return nullptr;
}
