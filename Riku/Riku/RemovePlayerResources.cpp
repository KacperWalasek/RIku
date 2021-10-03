//Kacper Walasek
#include "RemovePlayerResources.h"

RemovePlayerResources::RemovePlayerResources(int player, int resource, int quantity) : player(player), resource(resource), quantity(quantity) {}

int RemovePlayerResources::apply(GameState& state) const
{
    state.players[player].useResources(resource, quantity);
    return 0;
}

bool RemovePlayerResources::isDoable(const GameState& state) const
{
    return player < state.players.size() && state.players[player].getResourceQuantity(resource) > quantity;
}
