#include "InvitedPlayersRequestHandler.h"
#include "../Responses/InvitationResponse.h"
InvitedPlayersRequestHandler::InvitedPlayersRequestHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<Response> InvitedPlayersRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<InvitationResponse>(request, state.invitedPlayers);
}

bool InvitedPlayersRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "invited_players";
}
