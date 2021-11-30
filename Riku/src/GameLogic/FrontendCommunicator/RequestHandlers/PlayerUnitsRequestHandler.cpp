#include "PlayerUnitsRequestHandler.h"
#include "../Responses/UnitListResponse.h"

PlayerUnitsRequestHandler::PlayerUnitsRequestHandler(const GameState& gameState) 
    : player(gameState.players[gameState.playerOnMove]) 
{
    // TODO: zamiast obecnie graj¹cego gracza powinien byæ ostatni lokalny
}

std::shared_ptr<Response> PlayerUnitsRequestHandler::handleRequest(std::shared_ptr<Request> request) const
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
