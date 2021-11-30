#include "PlayerResourcesRequestHandler.h"
#include "../Responses/StringIntMapResponse.h"

PlayerResourcesRequestHandler::PlayerResourcesRequestHandler(const GameState& gamestate, const LogicAssets& assets)
    : player(gamestate.players[gamestate.playerOnMove]), assets(assets)
{
    // TODO: zamiast obecnie graj¹cego gracza ostatni lokalny
}

std::shared_ptr<Response> PlayerResourcesRequestHandler::handleRequest(std::shared_ptr<Request> request) const
{
    const auto& quantities = player.getResourceQuantities();
    std::map<std::string, int> resourceMap;
    std::transform(quantities.begin(), quantities.end(), 
        assets.playerResources.begin(),
        std::inserter(resourceMap,resourceMap.begin()),
        [](const int& quant, const Resource& res) {
            return std::pair < std::string, int >(res.getName(), quant);
        }
    );
    return std::make_shared<StringIntMapResponse>(request, resourceMap);
}

bool PlayerResourcesRequestHandler::canHandle(const Request& request) const
{
    return request.getKey() == "player_resources";
}
