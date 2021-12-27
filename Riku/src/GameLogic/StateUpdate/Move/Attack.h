#pragma once
#include "IMove.h"
#include "../../Unit/Unit.h"
#include "../Patch/MiniGamePatch.h"
#include "../../GameState.h"

class Attack :
    public IMove
{
    int player;
    std::pair<int, int> attackedTile;
    std::shared_ptr<Unit> unit;
public:
    Attack(int player, std::pair<int,int> attackedTile, std::shared_ptr<Unit> unit);

    // Odziedziczono za poœrednictwem elementu IMove
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;

    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;

    virtual std::shared_ptr<IMove> asPointner() const override;

};

