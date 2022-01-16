#include "InviteMoveHandler.h"
#include "../../../Network/WebModule.h"
#include "../MoveDescriptions/StringMoveDescription.h"
#include "../../GameState.h"

InviteMoveHandler::InviteMoveHandler( GameState& state)
	: state(state) {}

std::shared_ptr<IMove> InviteMoveHandler::handleDescription(const IMoveDescription& description)
{
	const auto& desc = (const StringMoveDescription&)description;
	Network::WebModule::Invite(desc.get(), state.name);
	state.invitedPlayers.emplace(desc.get(), Invitation(desc.get(), ""));
	return nullptr;
}

bool InviteMoveHandler::canHandle(const IMoveDescription& description) const
{
	return description.getMoveType() == "invite";
}

