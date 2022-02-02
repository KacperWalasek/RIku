#include "QuitGame.h"

std::shared_ptr<Patch> QuitGame::createPatch(const GameState& state, const LogicAssets& assets) const
{
    Patch patch = Patch();
    patch.clearGameState = true;
    return std::make_shared<Patch>(patch);
}

bool QuitGame::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
    return state.isInGame;
}

std::shared_ptr<IMove> QuitGame::asPointner() const
{
    return std::make_shared<QuitGame>();
}
