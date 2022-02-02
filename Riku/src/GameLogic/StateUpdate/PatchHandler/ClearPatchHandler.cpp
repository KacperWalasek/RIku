#include "ClearPatchHandler.h"
#include "../../Utils/LogicUtils.h"

std::shared_ptr<IAction> ClearPatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
    if (patch.clearGameState)
    {
        state.invitedPlayers.clear();
        state.map.clear();
        state.minigames.clear();
        state.playerOnMove = -1;
        state.players.clear();
        state.registredHookables.clear();
        LogicUtils::clearHookables();
        LogicUtils::resetPlayerIndexes();
        state.winner = -1;
        state.isInGame = false;
        state.hotSeatPlayers.clear();
        state.hotSeatPlayers.push_back(0);
    }
    return nullptr;
}
