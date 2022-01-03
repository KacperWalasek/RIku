#include "FinishMiniGame.h"
#include "../Patch/Patch.h"

FinishMiniGame::FinishMiniGame(int player, int enemy, int winner)
    : player(player), enemy(enemy), winner(winner)
{
}

std::shared_ptr<Patch> FinishMiniGame::createPatch(const GameState& state, const LogicAssets& assets) const
{
    // TODO make winner actualy win
    return std::make_shared<Patch>(MiniGamePatch(player,false,true) + (Patch)MiniGamePatch(enemy, false, true));
}

bool FinishMiniGame::isDoable(const GameState& state, const LogicAssets& assets) const
{
    auto end = state.minigames.end();
    return state.minigames.find(player) != end && state.minigames.find(enemy) != end;
}

std::shared_ptr<IMove> FinishMiniGame::asPointner() const
{
    return std::make_shared<FinishMiniGame>(player, enemy, winner);
}
