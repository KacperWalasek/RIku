#include "ClearPatchHandler.h"

std::shared_ptr<IAction> ClearPatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
    if (patch.clearGameState)
    {
        state.map.clear();
        state.minigames.clear();
        state.playerOnMove = 0;
        state.players.clear();
        state.registredHookables.clear();
    }
    return nullptr;
}
