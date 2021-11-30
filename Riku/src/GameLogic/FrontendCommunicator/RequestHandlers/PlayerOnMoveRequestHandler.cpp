#include "PlayerOnMoveRequestHandler.h"
#include "../Responses/IntResponse.h"
PlayerOnMoveRequestHandler::PlayerOnMoveRequestHandler(const GameState& state)
    : state(state)
{}

std::shared_ptr<Response> PlayerOnMoveRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<IntResponse>(request, state.playerOnMove);
}

bool PlayerOnMoveRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "player_on_move";
}
