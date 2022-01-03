#include "FinishMiniTurnMoveHandler.h"
#include "../StateUpdate/Move/FinishMiniTurn.h"
std::shared_ptr<IMiniMove> FinishMiniTurnMoveHandler::handleDescription(const IMoveDescription& description)
{
    return std::make_shared<FinishMiniTurn>();
}

bool FinishMiniTurnMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "finish_turn";
}
