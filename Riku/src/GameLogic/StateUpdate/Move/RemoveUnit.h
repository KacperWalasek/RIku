#pragma once
#include "IMove.h"
#include "../../Unit/Unit.h"
class RemoveUnit :
    public IMove
{
    int mapX, mapY;
public:
    RemoveUnit(int mapX, int mapY);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;
    virtual std::shared_ptr<IMove> asPointner() const override;
};

