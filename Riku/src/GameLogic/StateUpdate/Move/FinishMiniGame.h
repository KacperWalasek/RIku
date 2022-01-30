#pragma once
#include "IMove.h"
class FinishMiniGame :
    public IMove
{
    int player, enemy;
    std::shared_ptr<IMove> moveOnWin;
public:
    FinishMiniGame(int player, int enemy, std::shared_ptr<IMove> moveOnWin);

    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets, bool popup = false) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;
};

