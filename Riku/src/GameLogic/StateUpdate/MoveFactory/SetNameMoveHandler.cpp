#include "SetNameMoveHandler.h"
#include "../MoveDescriptions/StringMoveDescription.h"
#include "../../GameState.h"

SetNameMoveHandler::SetNameMoveHandler(GameState& state)
	: state(state) {}

std::shared_ptr<IMove> SetNameMoveHandler::handleDescription(const IMoveDescription& description)
{
	const auto& desc = (const StringMoveDescription&)description;
	state.name = desc.get();
	return nullptr;
}

bool SetNameMoveHandler::canHandle(const IMoveDescription& description) const
{
	return description.getMoveType() == "set_name";
}
