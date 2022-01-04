#include "PlayerOnMoveMiniRequestHandler.h"
#include "../../../GameLogic/FrontendCommunicator/Responses/IntResponse.h"

minigame::PlayerOnMoveMiniRequestHandler::PlayerOnMoveMiniRequestHandler(const MiniGameState& state)
    : state(state)
{
}

std::shared_ptr<Response> minigame::PlayerOnMoveMiniRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<IntResponse>(request, state.playerOnMove);
}

bool minigame::PlayerOnMoveMiniRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "player_on_move";
}
