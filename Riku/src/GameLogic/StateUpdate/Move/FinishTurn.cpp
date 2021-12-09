#include "FinishTurn.h"
#include "CombinedMove.h"

std::shared_ptr<Patch> FinishTurn::createPatch(const GameState& state, const LogicAssets& assets) const
{
    std::shared_ptr<IMove> move = nullptr;
    for (auto h : state.registredHookables)
        if(h->getOwner()==state.playerOnMove)
            move = move ? std::make_shared<CombinedMove>(move, h->onTurnEnd()) : h->onTurnEnd();
    std::shared_ptr<Patch> patch = move ? move->createPatch(state, assets) : std::make_shared<Patch>();
    for (auto unit : state.players[state.playerOnMove].units)
    {
        patch = std::make_shared<Patch>(*patch + UnitPatch(unit, unit->baseMovementPoints));
    }
    int nextPlayer = (state.playerOnMove + 1) % state.players.size();
    return std::make_shared<Patch>(Patch(nextPlayer) + *patch);
}

bool FinishTurn::isDoable(const GameState& state, const LogicAssets& assets) const
{
    return true;
}

std::shared_ptr<IMove> FinishTurn::asPointner() const
{
    return std::make_shared<FinishTurn>();
}
