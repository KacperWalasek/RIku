#include "ResignMiniMoveHandler.h"
#include "../StateUpdate/Move/MiniResign.h"

std::shared_ptr<IMiniMove> ResignMiniMoveHandler::handleDescription(const IMoveDescription& description)
{
    return std::make_shared<MiniResign>();
}

bool ResignMiniMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "resign";
}
