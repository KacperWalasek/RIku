#include "AcceptInvitationMoveHandler.h"
#include "../MoveDescriptions/StringMoveDescription.h"
#include "../../../Network/WebModule.h"
#include "../../GameState.h"

AcceptInvitationMoveHandler::AcceptInvitationMoveHandler(GameState& state)
    : state(state) {}


std::shared_ptr<IMove> AcceptInvitationMoveHandler::handleDescription(const IMoveDescription& description)
{
    const auto& desc = (const StringMoveDescription&)description;
    if (state.recivedInvitations.find(desc.get()) == state.recivedInvitations.end())
        return nullptr;
    Network::WebModule::AcceptInvitation(desc.get(), state.name);
    state.recivedInvitations.erase(desc.get());
    return nullptr;
}

bool AcceptInvitationMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "accept_invitation";
}
