#include "IsInMiniGameRequestHandler.h"
#include "../Responses/BoolResponse.h"

IsInMiniGameRequestHandler::IsInMiniGameRequestHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<Response> IsInMiniGameRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<BoolResponse>(request, state.minigames.find(state.playerOnMove) != state.minigames.end());
}

bool IsInMiniGameRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "is_in_minigame";
}
