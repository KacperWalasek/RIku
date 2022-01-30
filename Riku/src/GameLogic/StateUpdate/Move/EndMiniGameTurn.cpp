#include "EndMiniGameTurn.h"
#include "../../IMiniGame.h"
#include "../Patch/Patch.h"
EndMiniGameTurn::EndMiniGameTurn(int player, int enemy)
	: player(player), enemy(enemy)
{}

std::shared_ptr<Patch> EndMiniGameTurn::createPatch(const GameState& state, const LogicAssets& assets) const
{
	auto patch = state.minigames.find(player)->second->getCummulatedPatch();
	
	return std::make_shared<Patch>(MiniGamePatch(player, true, false) + (Patch)MiniGamePatch(enemy, patch));
}

bool EndMiniGameTurn::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
	return state.minigames.find(player) != state.minigames.end();
}

std::shared_ptr<IMove> EndMiniGameTurn::asPointner() const
{
	return std::make_shared<EndMiniGameTurn>(player, enemy);
}
