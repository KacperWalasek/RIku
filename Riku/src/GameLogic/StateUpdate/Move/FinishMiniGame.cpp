#include "FinishMiniGame.h"
#include "../Patch/Patch.h"

FinishMiniGame::FinishMiniGame(int player, int enemy, std::shared_ptr<IMove> moveOnWin)
    : player(player), enemy(enemy), moveOnWin(moveOnWin) {}

std::shared_ptr<Patch> FinishMiniGame::createPatch(const GameState& state, const LogicAssets& assets) const
{
    std::shared_ptr<Patch> winningPatch = moveOnWin ? moveOnWin->createPatch(state, assets) : std::make_shared<Patch>();
    return std::make_shared<Patch>(MiniGamePatch(player,false,true) 
        + (Patch)MiniGamePatch(enemy, false, true) 
        + *winningPatch);
}

bool FinishMiniGame::isDoable(const GameState& state, const LogicAssets& assets) const
{
    return state.minigames.find(player) != state.minigames.end();
}

std::shared_ptr<IMove> FinishMiniGame::asPointner() const
{
    return std::make_shared<FinishMiniGame>(player, enemy, moveOnWin);
}
