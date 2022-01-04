#include "MiniResign.h"
#include "../Patch/MiniPatch.h"
#include "../../MiniGameState.h"

std::shared_ptr<minigame::MiniPatch> minigame::MiniResign::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
    return std::make_shared<MiniPatch>(state.enemy.logicIndex, true);
}

bool minigame::MiniResign::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
    return true;
}

std::shared_ptr<minigame::IMiniMove> minigame::MiniResign::asPointner() const
{
    return std::make_shared<MiniResign>();
}
