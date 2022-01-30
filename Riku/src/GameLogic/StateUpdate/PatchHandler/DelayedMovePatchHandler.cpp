#include "DelayedMovePatchHandler.h"
#include "../../Actions/DelayedMoveAction.h"

std::shared_ptr<IAction> DelayedMovePatchHandler::handlePatch(GameState& state, const Patch& patch) const
{
    if (patch.delayedMove)
        return std::make_shared<DelayedMoveAction>(patch.delayedMove);
    return nullptr;
}
