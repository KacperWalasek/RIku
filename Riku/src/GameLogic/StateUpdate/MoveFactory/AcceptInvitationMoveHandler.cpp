#include "AcceptInvitationMoveHandler.h"
#include "../MoveDescriptions/AcceptInvitationMoveDescription.h"
#include "../../../Network/WebModule.h"
#include "../../GameState.h"

AcceptInvitationMoveHandler::AcceptInvitationMoveHandler(GameState& state)
    : state(state) {}


std::shared_ptr<IMove> AcceptInvitationMoveHandler::handleDescription(const IMoveDescription& description)
{
    const auto& desc = (const AcceptInvitationMoveDescription&)description;
    if (state.recivedInvitations.find(desc.getIp()) == state.recivedInvitations.end())
        return nullptr;
    Network::WebModule::AcceptInvitation(desc.getIp(), state.name, desc.getHotseatCount());
    state.recivedInvitations.erase(desc.getIp());
    state.hotSeatPlayers.clear();
    // initialize hotseatPlayers from 0. We will increase it when Join is recived
    for (int i = 0; i < desc.getHotseatCount(); i++)
        state.hotSeatPlayers.push_back(i);
    
    return nullptr;
}

bool AcceptInvitationMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "accept_invitation";
}
