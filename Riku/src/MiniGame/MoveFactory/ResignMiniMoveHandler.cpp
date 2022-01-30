#include "ResignMiniMoveHandler.h"
#include "../StateUpdate/Move/MiniResign.h"

std::shared_ptr<minigame::IMiniMove> minigame::ResignMiniMoveHandler::handleDescription(const IMoveDescription& description)
{
    return std::make_shared<MiniResign>();
}

bool minigame::ResignMiniMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "resign";
}
