#include "WinnerRequestHandler.h"
#include "../Responses/IntResponse.h"

WinnerRequestHandler::WinnerRequestHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<Response> WinnerRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<IntResponse>(request, state.winner);
}

bool WinnerRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "winner";
}
