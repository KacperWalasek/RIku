#include "UseResources.h"
#include <memory>
#include "../../LogicAssets.h"

int UseResources::getResourceFromString(const LogicAssets& assets) const
{
    auto it = std::find_if(assets.playerResources.begin(), assets.playerResources.end(),
        [this](const auto& r) { return r.getName() == resourceAsString; });
    if (it == assets.playerResources.end())
        return 0;
    return std::distance(assets.playerResources.begin(), it);
}

UseResources::UseResources(std::string resource, int quantity)
    :resourceAsString(resource), quantity(quantity), asString(true), resource(0)
{
}

UseResources::UseResources(int resource, int quantity)
    :resource(resource), quantity(quantity), asString(false)
{}

std::shared_ptr<Patch> UseResources::createPatch(const GameState& state, const LogicAssets& assets) const
{
    int res = asString ? getResourceFromString(assets) : resource;
    //TODO: player index
    return std::make_shared<Patch>(PlayerPatch(state.playerOnMove, res,-quantity));
}

bool UseResources::isDoable(const GameState& state, const LogicAssets& assets) const
{
    int res = asString ? getResourceFromString(assets) : resource;
    return state.players[state.playerOnMove].getResourceQuantity(res) >= quantity;
}

std::shared_ptr<IMove> UseResources::asPointner() const
{
    if (asString)
        return std::make_shared<UseResources>(resourceAsString, quantity);
    else
        return std::make_shared<UseResources>(resource,quantity);
}
