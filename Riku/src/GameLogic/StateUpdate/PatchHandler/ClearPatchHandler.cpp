#include "ClearPatchHandler.h"
#include "../../Utils/LogicUtils.h"

std::shared_ptr<IAction> ClearPatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
    if (patch.clearGameState)
    {
        state.invitedPlayers.clear();
        state.map.clear();
        state.minigames.clear();
        state.playerOnMove = 0;
        state.players.clear();
        state.registredHookables.clear();
        LogicUtils::clearHookables();
        LogicUtils::resetPlayerIndexes();
        state.isInGame = false;
        state.hotSeatPlayers.clear();
    }
    return nullptr;
}
