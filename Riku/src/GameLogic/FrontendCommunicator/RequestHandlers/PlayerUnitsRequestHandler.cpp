#include "PlayerUnitsRequestHandler.h"
#include "../Responses/UnitListResponse.h"

PlayerUnitsRequestHandler::PlayerUnitsRequestHandler(const GameState& gameState) 
    : player(gameState.players[0]) 
{
    // TODO: zamiast zerowego gracza, w stanie gry powinna by� informacja kt�rym graczem jeste�my
}

std::shared_ptr<Response> PlayerUnitsRequestHandler::handleRequest(std::shared_ptr<Request> request)
{
    std::vector<std::shared_ptr<const Unit>> units;
    std::copy(player.units.begin(), player.units.end(),
        std::back_inserter(units));
    return std::make_shared<UnitListResponse>(request, units);
}

bool PlayerUnitsRequestHandler::canHandle(const Request& request) const
{
    return request.getKey()=="player_units";
}
