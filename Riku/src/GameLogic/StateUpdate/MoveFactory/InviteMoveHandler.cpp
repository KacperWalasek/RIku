#include "InviteMoveHandler.h"
#include "../../../Network/WebModule.h"
#include "../MoveDescriptions/StringMoveDescription.h"
#include "../../GameState.h"
#include "../../Utils/LogicUtils.h"
#include <regex>

InviteMoveHandler::InviteMoveHandler( GameState& state)
	: state(state) {}

std::shared_ptr<IMove> InviteMoveHandler::handleDescription(const IMoveDescription& description)
{
	const auto& desc = (const StringMoveDescription&)description;
	if (desc.get() == Network::WebModule::getIp())
	{
		LogicUtils::addPopup("You cannot invite yourself!");
		return nullptr;
	}
	std::regex regex("^[0-9]+.[0-9]+.[0-9]+.[0-9]+$");
	if (!std::regex_match(desc.get(), regex))
	{
		LogicUtils::addPopup(desc.get() + " is not a valid Ip address");
		return nullptr;
	}
	Network::WebModule::Invite(desc.get(), state.name);
	state.invitedPlayers.emplace(desc.get(), Invitation(desc.get(), ""));
	return nullptr;
}

bool InviteMoveHandler::canHandle(const IMoveDescription& description) const
{
	return description.getMoveType() == "invite";
}

