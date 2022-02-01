#include "WinnerMiniRequestHandler.h"
#include "../../../GameLogic/FrontendCommunicator/Responses/IntResponse.h"
minigame::WinnerMiniRequestHandler::WinnerMiniRequestHandler(const MiniGameState& state)
    : state(state)
{
}

std::shared_ptr<Response> minigame::WinnerMiniRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<IntResponse>(request, state.winner);
}

bool minigame::WinnerMiniRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "winner";
}
