#include "HotseatCountMoveHandler.h"
#include "../../GameState.h"
#include "../MoveDescriptions/IntMoveDescription.h"
#include "../../Utils/LogicUtils.h"
HotseatCountMoveHandler::HotseatCountMoveHandler(GameState& state)
    : state(state) {}

std::shared_ptr<IMove> HotseatCountMoveHandler::handleDescription(const IMoveDescription& description)
{
    const auto& desc = (const IntMoveDescription&)description;
    if (desc.get() > 1)
        for (int i = 0; i < desc.get() - 1; i++)
            state.hotSeatPlayers.push_back(LogicUtils::getAvailablePlayerId());
    return nullptr;
}

bool HotseatCountMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "hotseat_count";
}
