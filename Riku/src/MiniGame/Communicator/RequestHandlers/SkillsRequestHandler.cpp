#include "SkillsRequestHandler.h"
#include "../Responses/MiniMapResponse.h"
#include "../../../GameLogic/FrontendCommunicator/Responses/StringListResponse.h"

minigame::SkillsRequestHandler::SkillsRequestHandler(const MiniGameState& state)
    : state(state) {}

std::shared_ptr<Response> minigame::SkillsRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    return std::make_shared<StringListResponse>(request, state.player.skills);
}

bool minigame::SkillsRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "skills";
}
