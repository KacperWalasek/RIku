//Kacper Walasek
#include "GenerateResources.h"

GenerateResources::GenerateResources(int player, int resource, int quantity, int mapX, int mapY, int requiredResource)
    : player(player), resource(resource), requiredResource(requiredResource), quantity(quantity), mapX(mapX), mapY(mapY) {}

std::shared_ptr<Patch> GenerateResources::createPatch(const GameState& state) const
{
    return std::make_shared<Patch>(PlayerPatch(player,resource,quantity));
}

bool GenerateResources::isDoable(const GameState& state) const
{  
    return player < state.players.size() 
        && state.players[player].getResourceQuantity(resource) + quantity >= 0 
        && (requiredResource < 0 || state.map[mapX][mapY].resource == requiredResource);
}
