#include "AttackMiniMoveHandler.h"
#include "../../GameLogic/StateUpdate/MoveDescriptions/AttackMoveDescription.h"
#include "../StateUpdate/Move/MiniAttack.h"

minigame::AttackMiniMoveHandler::AttackMiniMoveHandler(const MiniGameState& state)
    : state(state) {}

std::shared_ptr<minigame::IMiniMove> minigame::AttackMiniMoveHandler::handleDescription(const IMoveDescription& description)
{
    const AttackMoveDescription& desc = (const AttackMoveDescription&)description;
    auto& unit = state.map[desc.getFromX()][desc.getFromY()].unit;
    return std::make_shared<MiniAttack>(std::make_pair(desc.getToX(), desc.getToY()), unit);
}

bool minigame::AttackMiniMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "attack";
}
