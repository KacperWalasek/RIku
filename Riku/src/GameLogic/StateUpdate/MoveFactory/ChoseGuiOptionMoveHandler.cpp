#include "ChoseGuiOptionMoveHandler.h"
#include "../MoveDescriptions/ChoseGuiOptionMoveDescription.h"
ChoseGuiOptionMoveHandler::ChoseGuiOptionMoveHandler(const GameState& state)
    : state(state)
{}

std::shared_ptr<IMove> ChoseGuiOptionMoveHandler::handleDescription(const IMoveDescription& description)
{
    const ChoseGuiOptionMoveDescription& desc = (const ChoseGuiOptionMoveDescription&)description;
    return state.map[desc.getMapX()][desc.getMapY()].object->onOptionChosen(desc.getIndex());
}

bool ChoseGuiOptionMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "chose_gui_option";
}
