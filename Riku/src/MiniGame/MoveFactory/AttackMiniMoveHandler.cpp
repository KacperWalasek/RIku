#include "AttackMiniMoveHandler.h"
#include "../../GameLogic/StateUpdate/MoveDescriptions/AttackMoveDescription.h"
#include "../StateUpdate/Move/MiniAttack.h"

AttackMiniMoveHandler::AttackMiniMoveHandler(const MiniGameState& state)
    : state(state) {}

std::shared_ptr<IMiniMove> AttackMiniMoveHandler::handleDescription(const IMoveDescription& description)
{
    const AttackMoveDescription& desc = (const AttackMoveDescription&)description;
    auto& unit = state.map[desc.getFromX()][desc.getFromY()].unit;
    return std::make_shared<MiniAttack>(std::make_pair(desc.getToX(), desc.getToY()), unit);
}

bool AttackMiniMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "attack";
}
