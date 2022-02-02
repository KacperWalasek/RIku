#include "HotseatPlayersRequestHandler.h"
#include "../Responses/IntListResponse.h"

HotseatPlayersRequestHandler::HotseatPlayersRequestHandler(const GameState& state)
    : state(state)
{
}

std::shared_ptr<Response> HotseatPlayersRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<IntListResponse>(request, state.hotSeatPlayers);
}

bool HotseatPlayersRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "hotseat_players";
}
