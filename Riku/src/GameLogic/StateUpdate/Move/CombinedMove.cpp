#include "CombinedMove.h"

CombinedMove::CombinedMove(MoveWrapper w1, MoveWrapper w2)
    : move1(w1.move), move2(w2.move)
{}

CombinedMove::CombinedMove(std::shared_ptr<IMove> move1, std::shared_ptr<IMove> move2)
    : move1(move1), move2(move2)
{}

std::shared_ptr<Patch> CombinedMove::createPatch(const GameState& state, const LogicAssets& assets) const
{
    auto p1 = move1 == nullptr ? std::make_shared<Patch>() : move1->createPatch(state, assets);
    auto p2 = move2 == nullptr ? std::make_shared<Patch>() : move2->createPatch(state, assets);
    return std::make_shared<Patch>(*p1 + *p2);
}

bool CombinedMove::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
    return (move1==nullptr || move1->isDoable(state, assets, popup)) && (move2==nullptr || move2->isDoable(state, assets, popup));
}

std::shared_ptr<IMove> CombinedMove::asPointner() const
{
    return std::make_shared<CombinedMove>(move1,move2);
}
