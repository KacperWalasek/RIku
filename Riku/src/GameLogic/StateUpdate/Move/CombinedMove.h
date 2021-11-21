#pragma once
#include "IMove.h"
#include "../Patch/Patch.h"

class CombinedMove :
    public IMove
{
    std::shared_ptr<IMove> move1, move2;
public:
    CombinedMove(std::shared_ptr<IMove> move1, std::shared_ptr<IMove> move2);
    virtual std::shared_ptr<Patch> createPatch(const GameState& state) const override;

    virtual bool isDoable(const GameState& state) const override;

    virtual std::shared_ptr<IMove> asPointner() const override;

};

