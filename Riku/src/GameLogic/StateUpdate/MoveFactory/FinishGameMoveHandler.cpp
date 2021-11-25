#include "FinishGameMoveHandler.h"
#include "../Move/FinishTurn.h"

std::shared_ptr<IMove> FinishGameMoveHandler::handleDescription(const IMoveDescription& description)
{
    return std::make_shared<FinishTurn>();
}

bool FinishGameMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType()=="finish_turn";
}
