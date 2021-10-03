//Kacper Walasek
#include "AddPlayerResources.h"

AddPlayerResources::AddPlayerResources(int player, int resource, int quantity) : player(player), resource(resource), quantity(quantity) {}

int AddPlayerResources::apply(GameState& state) const
{
    state.players[player].acceptResources(resource, quantity);
    return 0;
}

bool AddPlayerResources::isDoable(const GameState& state) const
{
    return player < state.players.size();
}
