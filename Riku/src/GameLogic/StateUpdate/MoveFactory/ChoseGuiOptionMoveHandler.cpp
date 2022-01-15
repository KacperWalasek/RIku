#include "ChoseGuiOptionMoveHandler.h"
#include "../MoveDescriptions/ChoseGuiOptionMoveDescription.h"
#include "../../Hooks/GUIDescription.h"
ChoseGuiOptionMoveHandler::ChoseGuiOptionMoveHandler(const GameState& state)
    : state(state)
{}

std::shared_ptr<IMove> ChoseGuiOptionMoveHandler::handleDescription(const IMoveDescription& description)
{
    const ChoseGuiOptionMoveDescription& desc = (const ChoseGuiOptionMoveDescription&)description;
    return state.map[desc.getMapX()][desc.getMapY()].object->onOptionChosen(desc.getIndex(), desc.getMapX(), desc.getMapY());
}

bool ChoseGuiOptionMoveHandler::canHandle(const IMoveDescription& description) const
{
    if (description.getMoveType() != "chose_gui_option")
        return false;
    const ChoseGuiOptionMoveDescription& desc = (const ChoseGuiOptionMoveDescription&)description;
    auto object = state.map[desc.getMapX()][desc.getMapY()].object;
    return object && object->getGuiDescription().getOptions().size() > desc.getIndex();
}
