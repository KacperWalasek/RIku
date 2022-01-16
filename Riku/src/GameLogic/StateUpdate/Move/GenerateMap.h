#pragma once
#include "IMove.h"
class GenerateMap :
    public IMove
{
    int playerCount;
public:
    GenerateMap(int playerCount);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;

    virtual bool isDoable(const GameState& state, const LogicAssets& assets) const override;

    virtual std::shared_ptr<IMove> asPointner() const override;

};

