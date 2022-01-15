#include "InvitationsRequestHandler.h"
#include "../Responses/StringStringMapResponse.h"
InvitationsRequestHandler::InvitationsRequestHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<Response> InvitationsRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<StringStringMapResponse>(request, state.recivedInvitations);
}

bool InvitationsRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "invitations";
}
