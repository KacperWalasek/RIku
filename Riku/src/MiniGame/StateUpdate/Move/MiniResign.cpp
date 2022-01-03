#include "MiniResign.h"
#include "../Patch/MiniPatch.h"
#include "../../MiniGameState.h"

std::shared_ptr<MiniPatch> MiniResign::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    return std::make_shared<MiniPatch>(state.enemy.logicIndex, true);
}

bool MiniResign::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    return true;
}

std::shared_ptr<IMiniMove> MiniResign::asPointner() const
{
    return std::make_shared<MiniResign>();
}
