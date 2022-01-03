#include "FinishMiniTurn.h"
#include "../Patch/MiniPatch.h"

std::shared_ptr<MiniPatch> FinishMiniTurn::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
	return std::make_shared<MiniPatch>(state.enemy.logicIndex);
}

bool FinishMiniTurn::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
	return state.playerOnMove == state.player.logicIndex;
}

std::shared_ptr<IMiniMove> FinishMiniTurn::asPointner() const
{
	return std::make_shared<FinishMiniTurn>();
}
