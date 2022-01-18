#include "PlayerCountRequestHandler.h"
#include "../Responses/IntResponse.h"

PlayerCountRequestHandler::PlayerCountRequestHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<Response> PlayerCountRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<IntResponse>(request, state.players.size());
}

bool PlayerCountRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "player_count";
}
