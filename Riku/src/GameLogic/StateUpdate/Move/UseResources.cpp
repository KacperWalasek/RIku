#include "UseResources.h"
#include <memory>

UseResources::UseResources(int resource, int quantity)
    :resource(resource), quantity(quantity)
{}

std::shared_ptr<Patch> UseResources::createPatch(const GameState& state, const LogicAssets& assets) const
{
    //TODO: player index
    return std::make_shared<Patch>(PlayerPatch(state.playerOnMove,resource,-quantity));
}

bool UseResources::isDoable(const GameState& state, const LogicAssets& assets) const
{
    return state.players[0].getResourceQuantity(resource) <= quantity;
}

std::shared_ptr<IMove> UseResources::asPointner() const
{
    return std::make_shared<UseResources>(resource,quantity);
}
