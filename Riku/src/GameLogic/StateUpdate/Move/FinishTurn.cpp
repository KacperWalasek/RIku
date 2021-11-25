#include "FinishTurn.h"
#include "CombinedMove.h"

std::shared_ptr<Patch> FinishTurn::createPatch(const GameState& state, const LogicAssets& assets) const
{
    std::shared_ptr<IMove> move = nullptr;
    for (auto h : state.registredHookables)
    {
        move = move ? std::make_shared<CombinedMove>(move, h->onTurnEnd()) : h->onTurnEnd();
    }
    return move ? move->createPatch(state, assets) : std::make_shared<Patch>();
}

bool FinishTurn::isDoable(const GameState& state, const LogicAssets& assets) const
{
    return true;
}

std::shared_ptr<IMove> FinishTurn::asPointner() const
{
    return std::make_shared<FinishTurn>();
}
