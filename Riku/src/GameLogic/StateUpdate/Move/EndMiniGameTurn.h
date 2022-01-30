#pragma once
#include "IMove.h"
#include "../../GameState.h"

class EndMiniGameTurn :
    public IMove
{
    int player;
    int enemy;
public:
    EndMiniGameTurn(int player, int enemy);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;

    virtual bool isDoable(const GameState& state, const LogicAssets& assets, bool popup = false) const override;

    virtual std::shared_ptr<IMove> asPointner() const override;

};

