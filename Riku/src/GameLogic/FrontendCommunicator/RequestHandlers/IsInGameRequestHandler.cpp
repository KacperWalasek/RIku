#include "IsInGameRequestHandler.h"
#include "../Responses/BoolResponse.h"
IsInGameRequestHandler::IsInGameRequestHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<Response> IsInGameRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<BoolResponse>(request, state.isInGame);
}

bool IsInGameRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "is_in_game";
}
