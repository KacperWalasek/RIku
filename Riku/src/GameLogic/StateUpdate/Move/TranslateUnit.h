#pragma once
#include "IMove.h"
#include "../Patch/Patch.h"
#include "../../GameState.h"
class TranslateUnit :
    public IMove
{
    int fromX, fromY, toX, toY;
public:
    TranslateUnit(int fromX, int fromY, int toX, int toY);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;
};

