#include "FinishMiniTurn.h"
#include "../Patch/MiniPatch.h"

std::shared_ptr<minigame::MiniPatch> minigame::FinishMiniTurn::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
	if (state.enemy.units.size() == 0)
		return std::make_shared<MiniPatch>(state.player.logicIndex, true);
	if (state.player.units.size() == 0)
		return std::make_shared<MiniPatch>(state.enemy.logicIndex, true);

	return std::make_shared<MiniPatch>(state.enemy.logicIndex);
}

bool minigame::FinishMiniTurn::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
	return state.playerOnMove == state.player.logicIndex;
}

std::shared_ptr<minigame::IMiniMove> minigame::FinishMiniTurn::asPointner() const
{
	return std::make_shared<FinishMiniTurn>();
}
