//Kacper Walasek
#include "ExtractResources.h"
#include "../Patch/Patch.h"
ExtractResources::ExtractResources(int player, int resource, int quantity, int mapX, int mapY, int requiredResource)
    : player(player), resource(resource), requiredResource(requiredResource), quantity(quantity), mapX(mapX), mapY(mapY) {}

std::shared_ptr<Patch> ExtractResources::createPatch(const GameState& state, const LogicAssets& assets) const
{
    // TODO: operator ?: nie bêdzie potrzebny jak onTurnEnd bedzie mial dostep do GameState. Poprawiæ wtedy w ResourceFactory
    return std::make_shared<Patch>(PlayerPatch(player < 0 ? state.playerOnMove : player,resource,quantity));
}

bool ExtractResources::isDoable(const GameState& state, const LogicAssets& assets) const
{  
    return player < state.players.size() 
        && state.players[player].getResourceQuantity(resource) + quantity >= 0 
        && (requiredResource < 0 || state.map[mapX][mapY].resource == requiredResource);
}

std::shared_ptr<IMove> ExtractResources::asPointner() const
{
    return std::make_shared<ExtractResources>(player, resource, quantity, mapX, mapY, requiredResource);
}
