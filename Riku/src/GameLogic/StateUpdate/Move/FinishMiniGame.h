#pragma once
#include "IMove.h"
class FinishMiniGame :
    public IMove
{
    int player, enemy, winner;
public:
    FinishMiniGame(int player, int enemy, int winner);

    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;
};

