#include "AttackMoveHandler.h"
#include "../MoveDescriptions/AttackMoveDescription.h"
#include "../Move/Attack.h"

AttackMoveHandler::AttackMoveHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<IMove> AttackMoveHandler::handleDescription(const IMoveDescription& description)
{
    const AttackMoveDescription& desc = (const AttackMoveDescription&)description;
    auto& unit = state.map[desc.getFromX()][desc.getFromY()].unit;
    return std::make_shared<Attack>(state.playerOnMove,std::make_pair(desc.getToX(),desc.getToY()),unit);
}

bool AttackMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "attack";
}
