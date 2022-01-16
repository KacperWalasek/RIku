#include "IsInMiniGameRequestHandler.h"
#include "../Responses/BoolResponse.h"
#include "../../IMiniGame.h"
#include "../../Utils/LogicUtils.h"
IsInMiniGameRequestHandler::IsInMiniGameRequestHandler(const GameState& state)
    : state(state) {}

std::shared_ptr<Response> IsInMiniGameRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<BoolResponse>(request, state.minigames.find(LogicUtils::getResponsePlayer(state)) != state.minigames.end());
}

bool IsInMiniGameRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "is_in_minigame";
}
