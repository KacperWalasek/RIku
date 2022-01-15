#include "CombinedMiniMove.h"
#include "../Patch/MiniPatch.h"

minigame::CombinedMiniMove::CombinedMiniMove(MiniMoveWrapper w1, MiniMoveWrapper w2)
    : move1(w1.move), move2(w2.move)
{
}

minigame::CombinedMiniMove::CombinedMiniMove(std::shared_ptr<IMiniMove> move1, std::shared_ptr<IMiniMove> move2)
    : move1(move1), move2(move2)
{
}

std::shared_ptr<minigame::MiniPatch> minigame::CombinedMiniMove::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    auto p1 = move1 == nullptr ? std::make_shared<MiniPatch>() : move1->createPatch(state, assets);
    auto p2 = move2 == nullptr ? std::make_shared<MiniPatch>() : move2->createPatch(state, assets);
    return std::make_shared<MiniPatch>(*p1 + *p2);
}

bool minigame::CombinedMiniMove::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    return (move1 == nullptr || move1->isDoable(state, assets)) && (move2 == nullptr || move2->isDoable(state, assets));
}

std::shared_ptr<minigame::IMiniMove> minigame::CombinedMiniMove::asPointner() const
{
    return std::make_shared<CombinedMiniMove>(move1, move2);
}
