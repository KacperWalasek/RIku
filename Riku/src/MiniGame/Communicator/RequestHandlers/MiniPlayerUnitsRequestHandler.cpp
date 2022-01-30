#include "MiniPlayerUnitsRequestHandler.h"
#include "../Responses/MiniUnitListResponse.h"

minigame::MiniPlayerUnitsRequestHandler::MiniPlayerUnitsRequestHandler(const MiniGameState& gameState)
    : state(gameState) {}

std::shared_ptr<Response> minigame::MiniPlayerUnitsRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    std::vector<std::shared_ptr<const MiniUnit>> units;
    std::copy(state.player.units.begin(), state.player.units.end(),
        std::back_inserter(units));
    return std::make_shared<MiniUnitListResponse>(request, units);
}

bool minigame::MiniPlayerUnitsRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "mini_player_units";
}
