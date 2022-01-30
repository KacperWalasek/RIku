#include "FinishMiniTurnMoveHandler.h"
#include "../StateUpdate/Move/FinishMiniTurn.h"
std::shared_ptr<minigame::IMiniMove> minigame::FinishMiniTurnMoveHandler::handleDescription(const IMoveDescription& description)
{
    return std::make_shared<FinishMiniTurn>();
}

bool minigame::FinishMiniTurnMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "finish_turn";
}
