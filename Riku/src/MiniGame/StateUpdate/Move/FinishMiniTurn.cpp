#include "FinishMiniTurn.h"
#include "../Patch/MiniPatch.h"
#include "CombinedMiniMove.h"
#include "../../Utils/MiniGameUtils.h"

std::shared_ptr<minigame::MiniPatch> minigame::FinishMiniTurn::createPatch(const MiniGameState& state, const MiniGameAssets& assets) const
{
	if (state.enemy.units.size() == 0)
		return std::make_shared<MiniPatch>(state.player.logicIndex, true);
	if (state.player.units.size() == 0)
		return std::make_shared<MiniPatch>(state.enemy.logicIndex, true);

	std::shared_ptr<IMiniMove> move = nullptr;
	for (std::string id : state.registredHookables)
	{
		auto h = MiniGameUtils::getHookable(id);
		if (h->getOwner() == state.player.logicIndex)
			move = move ? std::make_shared<CombinedMiniMove>(move, h->onTurnEnd()) : h->onTurnEnd();
	}
	std::shared_ptr<MiniPatch> patch = move ? move->createPatch(state, assets) : std::make_shared<MiniPatch>();
	for (auto unit : state.player.units)
	{
		patch = std::make_shared<MiniPatch>(*patch + MiniUnitPatch(unit->getId(), unit->baseMovementPoints));
	}
	return std::make_shared<MiniPatch>(*patch + MiniPatch(state.enemy.logicIndex));
}

bool minigame::FinishMiniTurn::isDoable(const MiniGameState& state, const MiniGameAssets& assets) const
{
	return state.playerOnMove == state.player.logicIndex;
}

std::shared_ptr<minigame::IMiniMove> minigame::FinishMiniTurn::asPointner() const
{
	return std::make_shared<FinishMiniTurn>();
}
