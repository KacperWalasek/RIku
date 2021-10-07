//Kacper Walasek
#include "ChangePlayerResources.h"

ChangePlayerResources::ChangePlayerResources(int player, int resource, int quantity) : player(player), resource(resource), quantity(quantity) {}

std::shared_ptr<Patch> ChangePlayerResources::apply(const GameState& state) const
{
    return std::make_shared<Patch>(PlayerPatch(player,resource,quantity));
}

bool ChangePlayerResources::isDoable(const GameState& state) const
{  
    return player < state.players.size() && state.players[player].getResourceQuantity(resource) + quantity >= 0;
}
